
#include <google/protobuf/compiler/java/java_message_builder_lite.h>

#include <algorithm>
#include <google/protobuf/stubs/hash.h>
#include <map>
#include <memory>
#ifndef _SHARED_PTR_H
#include <google/protobuf/stubs/shared_ptr.h>
#endif
#include <vector>

#include <google/protobuf/compiler/java/java_context.h>
#include <google/protobuf/compiler/java/java_doc_comment.h>
#include <google/protobuf/compiler/java/java_enum.h>
#include <google/protobuf/compiler/java/java_extension.h>
#include <google/protobuf/compiler/java/java_generator_factory.h>
#include <google/protobuf/compiler/java/java_helpers.h>
#include <google/protobuf/compiler/java/java_name_resolver.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/wire_format.h>
#include <google/protobuf/stubs/strutil.h>
#include <google/protobuf/stubs/substitute.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace java {

namespace {
bool GenerateHasBits(const Descriptor* descriptor) {
  return SupportFieldPresence(descriptor->file()) ||
      HasRepeatedFields(descriptor);
}

string MapValueImmutableClassdName(const Descriptor* descriptor,
                                   ClassNameResolver* name_resolver) {
  const FieldDescriptor* value_field = descriptor->FindFieldByName("value");
  GOOGLE_CHECK_EQ(FieldDescriptor::TYPE_MESSAGE, value_field->type());
  return name_resolver->GetImmutableClassName(value_field->message_type());
}
}  // namespace

MessageBuilderLiteGenerator::MessageBuilderLiteGenerator(
    const Descriptor* descriptor, Context* context)
  : descriptor_(descriptor), context_(context),
    name_resolver_(context->GetNameResolver()),
    field_generators_(descriptor, context_) {
  GOOGLE_CHECK(!HasDescriptorMethods(descriptor->file(), context->EnforceLite()))
      << "Generator factory error: A lite message generator is used to "
         "generate non-lite messages.";
}

MessageBuilderLiteGenerator::~MessageBuilderLiteGenerator() {}

void MessageBuilderLiteGenerator::
Generate(io::Printer* printer) {
  WriteMessageDocComment(printer, descriptor_);
  printer->Print(
    "public static final class Builder extends\n"
    "    com.google.protobuf.GeneratedMessageLite.$extendible$Builder<\n"
    "      $classname$, Builder> implements\n"
    "    $extra_interfaces$\n"
    "    $classname$OrBuilder {\n",
    "classname", name_resolver_->GetImmutableClassName(descriptor_),
    "extra_interfaces", ExtraBuilderInterfaces(descriptor_),
    "extendible",
    descriptor_->extension_range_count() > 0 ? "Extendable" : "");
  printer->Indent();

  GenerateCommonBuilderMethods(printer);

  // oneof
  map<string, string> vars;
  for (int i = 0; i < descriptor_->oneof_decl_count(); i++) {
    vars["oneof_name"] = context_->GetOneofGeneratorInfo(
        descriptor_->oneof_decl(i))->name;
    vars["oneof_capitalized_name"] = context_->GetOneofGeneratorInfo(
        descriptor_->oneof_decl(i))->capitalized_name;
    vars["oneof_index"] = SimpleItoa(descriptor_->oneof_decl(i)->index());

    // oneofCase() and clearOneof()
    printer->Print(vars,
      "public $oneof_capitalized_name$Case\n"
      "    get$oneof_capitalized_name$Case() {\n"
      "  return instance.get$oneof_capitalized_name$Case();\n"
      "}\n"
      "\n"
      "public Builder clear$oneof_capitalized_name$() {\n"
      "  copyOnWrite();\n"
      "  instance.clear$oneof_capitalized_name$();\n"
      "  return this;\n"
      "}\n"
      "\n");
  }

  if (GenerateHasBits(descriptor_)) {
    // Integers for bit fields.
    int totalBits = 0;
    for (int i = 0; i < descriptor_->field_count(); i++) {
      totalBits += field_generators_.get(descriptor_->field(i))
          .GetNumBitsForBuilder();
    }
    int totalInts = (totalBits + 31) / 32;
    for (int i = 0; i < totalInts; i++) {
      printer->Print("private int $bit_field_name$;\n",
        "bit_field_name", GetBitFieldName(i));
    }
  }

  for (int i = 0; i < descriptor_->field_count(); i++) {
    printer->Print("\n");
    field_generators_.get(descriptor_->field(i))
                     .GenerateBuilderMembers(printer);
  }

  printer->Print(
    "\n"
    "// @@protoc_insertion_point(builder_scope:$full_name$)\n",
    "full_name", descriptor_->full_name());

  printer->Outdent();
  printer->Print("}\n");
}

// ===================================================================

void MessageBuilderLiteGenerator::
GenerateCommonBuilderMethods(io::Printer* printer) {
  printer->Print(
    "// Construct using $classname$.newBuilder()\n"
    "private Builder() {\n"
    "  super(DEFAULT_INSTANCE);\n"
    "}\n"
    "\n",
    "classname", name_resolver_->GetImmutableClassName(descriptor_));
}

// ===================================================================

}  // namespace java
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
