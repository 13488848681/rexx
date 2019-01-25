#include <google/protobuf/compiler/java/java_extension_lite.h>

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

ImmutableExtensionLiteGenerator::ImmutableExtensionLiteGenerator(
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

ImmutableExtensionLiteGenerator::~ImmutableExtensionLiteGenerator() {}

void ImmutableExtensionLiteGenerator::Generate(io::Printer* printer) {
  map<string, string> vars;
  const bool kUseImmutableNames = true;
  InitTemplateVars(descriptor_, scope_, kUseImmutableNames, name_resolver_,
                   &vars);
  printer->Print(vars,
      "public static final int $constant_name$ = $number$;\n");

  WriteFieldDocComment(printer, descriptor_);
  if (descriptor_->is_repeated()) {
    printer->Print(
        vars,
        "public static final\n"
        "  com.google.protobuf.GeneratedMessageLite.GeneratedExtension<\n"
        "    $containing_type$,\n"
        "    $type$> $name$ = com.google.protobuf.GeneratedMessageLite\n"
        "        .newRepeatedGeneratedExtension(\n"
        "      $containing_type$.getDefaultInstance(),\n"
        "      $prototype$,\n"
        "      $enum_map$,\n"
        "      $number$,\n"
        "      com.google.protobuf.WireFormat.FieldType.$type_constant$,\n"
        "      $packed$,\n"
        "      $singular_type$.class);\n");
  } else {
    printer->Print(
        vars,
        "public static final\n"
        "  com.google.protobuf.GeneratedMessageLite.GeneratedExtension<\n"
        "    $containing_type$,\n"
        "    $type$> $name$ = com.google.protobuf.GeneratedMessageLite\n"
        "        .newSingularGeneratedExtension(\n"
        "      $containing_type$.getDefaultInstance(),\n"
        "      $default$,\n"
        "      $prototype$,\n"
        "      $enum_map$,\n"
        "      $number$,\n"
        "      com.google.protobuf.WireFormat.FieldType.$type_constant$,\n"
        "      $singular_type$.class);\n");
  }
}

int ImmutableExtensionLiteGenerator::GenerateNonNestedInitializationCode(
    io::Printer* printer) {
  return 0;
}

int ImmutableExtensionLiteGenerator::GenerateRegistrationCode(
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
