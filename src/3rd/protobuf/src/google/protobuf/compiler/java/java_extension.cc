#include <google/protobuf/compiler/java/java_extension.h>

#include <google/protobuf/compiler/java/java_context.h>
#include <google/protobuf/compiler/java/java_doc_comment.h>
#include <google/protobuf/compiler/java/java_helpers.h>
#include <google/protobuf/compiler/java/java_name_resolver.h>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/stubs/strutil.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace java {

ImmutableExtensionGenerator::ImmutableExtensionGenerator(
    const FieldDescriptor* descriptor, Context* context)
  : descriptor_(descriptor), context_(context),
    name_resolver_(context->GetNameResolver()) {
  if (descriptor_->extension_scope() != NULL) {
    scope_ = name_resolver_->GetImmutableClassName(
        descriptor_->extension_scope());
  } else {
    scope_ = name_resolver_->GetImmutableClassName(descriptor_->file());
  }
}

ImmutableExtensionGenerator::~ImmutableExtensionGenerator() {}

// Initializes the vars referenced in the generated code templates.
void ExtensionGenerator::InitTemplateVars(const FieldDescriptor* descriptor,
                                          const string& scope,
                                          bool immutable,
                                          ClassNameResolver* name_resolver,
                                          map<string, string>* vars_pointer) {
  map<string, string> &vars = *vars_pointer;
  vars["scope"] = scope;
  vars["name"] = UnderscoresToCamelCase(descriptor);
  vars["containing_type"] =
      name_resolver->GetClassName(descriptor->containing_type(), immutable);
  vars["number"] = SimpleItoa(descriptor->number());
  vars["constant_name"] = FieldConstantName(descriptor);
  vars["index"] = SimpleItoa(descriptor->index());
  vars["default"] = descriptor->is_repeated() ?
      "" : DefaultValue(descriptor, immutable, name_resolver);
  vars["type_constant"] = FieldTypeName(GetType(descriptor));
  vars["packed"] = descriptor->options().packed() ? "true" : "false";
  vars["enum_map"] = "null";
  vars["prototype"] = "null";

  JavaType java_type = GetJavaType(descriptor);
  string singular_type;
  switch (java_type) {
    case JAVATYPE_MESSAGE:
      singular_type = name_resolver->GetClassName(descriptor->message_type(),
                                                   immutable);
      vars["prototype"] = singular_type + ".getDefaultInstance()";
      break;
    case JAVATYPE_ENUM:
      singular_type = name_resolver->GetClassName(descriptor->enum_type(),
                                                   immutable);
      vars["enum_map"] = singular_type + ".internalGetValueMap()";
      break;
    case JAVATYPE_STRING:
      singular_type = "java.lang.String";
      break;
    case JAVATYPE_BYTES:
      singular_type = immutable ? "com.google.protobuf.ByteString" : "byte[]";
      break;
    default:
      singular_type = BoxedPrimitiveTypeName(java_type);
      break;
  }
  vars["type"] = descriptor->is_repeated() ?
      "java.util.List<" + singular_type + ">" : singular_type;
  vars["singular_type"] = singular_type;
}

void ImmutableExtensionGenerator::Generate(io::Printer* printer) {
  map<string, string> vars;
  const bool kUseImmutableNames = true;
  InitTemplateVars(descriptor_, scope_, kUseImmutableNames, name_resolver_,
                   &vars);
  printer->Print(vars,
      "public static final int $constant_name$ = $number$;\n");

  WriteFieldDocComment(printer, descriptor_);
  if (descriptor_->extension_scope() == NULL) {
    // Non-nested
    printer->Print(
        vars,
        "public static final\n"
        "  com.google.protobuf.GeneratedMessage.GeneratedExtension<\n"
        "    $containing_type$,\n"
        "    $type$> $name$ = com.google.protobuf.GeneratedMessage\n"
        "        .newFileScopedGeneratedExtension(\n"
        "      $singular_type$.class,\n"
        "      $prototype$);\n");
  } else {
    // Nested
    printer->Print(
        vars,
        "public static final\n"
        "  com.google.protobuf.GeneratedMessage.GeneratedExtension<\n"
        "    $containing_type$,\n"
        "    $type$> $name$ = com.google.protobuf.GeneratedMessage\n"
        "        .newMessageScopedGeneratedExtension(\n"
        "      $scope$.getDefaultInstance(),\n"
        "      $index$,\n"
        "      $singular_type$.class,\n"
        "      $prototype$);\n");
  }
}

int ImmutableExtensionGenerator::GenerateNonNestedInitializationCode(
    io::Printer* printer) {
  int bytecode_estimate = 0;
  if (descriptor_->extension_scope() == NULL) {
    // Only applies to non-nested extensions.
    printer->Print(
        "$name$.internalInit(descriptor.getExtensions().get($index$));\n",
        "name", UnderscoresToCamelCase(descriptor_),
        "index", SimpleItoa(descriptor_->index()));
    bytecode_estimate += 21;
  }
  return bytecode_estimate;
}

int ImmutableExtensionGenerator::GenerateRegistrationCode(
    io::Printer* printer) {
  printer->Print(
    "registry.add($scope$.$name$);\n",
    "scope", scope_,
    "name", UnderscoresToCamelCase(descriptor_));
  return 7;
}

}  // namespace java
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
