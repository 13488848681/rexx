
#include <map>
#include <string>

#include <google/protobuf/compiler/objectivec/objectivec_oneof.h>
#include <google/protobuf/compiler/objectivec/objectivec_helpers.h>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/stubs/strutil.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace objectivec {

OneofGenerator::OneofGenerator(const OneofDescriptor* descriptor)
    : descriptor_(descriptor) {
  variables_["enum_name"] = OneofEnumName(descriptor_);
  variables_["name"] = OneofName(descriptor_);
  variables_["capitalized_name"] = OneofNameCapitalized(descriptor_);
  variables_["raw_index"] = SimpleItoa(descriptor_->index());
  const Descriptor* msg_descriptor = descriptor_->containing_type();
  variables_["owning_message_class"] = ClassName(msg_descriptor);

  string comments;
  SourceLocation location;
  if (descriptor_->GetSourceLocation(&location)) {
    comments = BuildCommentsString(location, true);
  } else {
    comments = "";
  }
  variables_["comments"] = comments;
}

OneofGenerator::~OneofGenerator() {}

void OneofGenerator::SetOneofIndexBase(int index_base) {
  int index = descriptor_->index() + index_base;
  // Flip the sign to mark it as a oneof.
  variables_["index"] = SimpleItoa(-index);
}

void OneofGenerator::GenerateCaseEnum(io::Printer* printer) {
  printer->Print(
      variables_,
      "typedef GPB_ENUM($enum_name$) {\n");
  printer->Indent();
  printer->Print(
      variables_,
      "$enum_name$_GPBUnsetOneOfCase = 0,\n");
  string enum_name = variables_["enum_name"];
  for (int j = 0; j < descriptor_->field_count(); j++) {
    const FieldDescriptor* field = descriptor_->field(j);
    string field_name = FieldNameCapitalized(field);
    printer->Print(
        "$enum_name$_$field_name$ = $field_number$,\n",
        "enum_name", enum_name,
        "field_name", field_name,
        "field_number", SimpleItoa(field->number()));
  }
  printer->Outdent();
  printer->Print(
      "};\n"
      "\n");
}

void OneofGenerator::GeneratePublicCasePropertyDeclaration(
    io::Printer* printer) {
  printer->Print(
      variables_,
      "$comments$"
      "@property(nonatomic, readonly) $enum_name$ $name$OneOfCase;\n"
      "\n");
}

void OneofGenerator::GenerateClearFunctionDeclaration(io::Printer* printer) {
  printer->Print(
      variables_,
      "/**\n"
      " * Clears whatever value was set for the oneof '$name$'.\n"
      " **/\n"
      "void $owning_message_class$_Clear$capitalized_name$OneOfCase($owning_message_class$ *message);\n");
}

void OneofGenerator::GeneratePropertyImplementation(io::Printer* printer) {
  printer->Print(
      variables_,
      "@dynamic $name$OneOfCase;\n");
}

void OneofGenerator::GenerateClearFunctionImplementation(io::Printer* printer) {
  printer->Print(
      variables_,
      "void $owning_message_class$_Clear$capitalized_name$OneOfCase($owning_message_class$ *message) {\n"
      "  GPBDescriptor *descriptor = [message descriptor];\n"
      "  GPBOneofDescriptor *oneof = [descriptor.oneofs objectAtIndex:$raw_index$];\n"
      "  GPBMaybeClearOneof(message, oneof, $index$, 0);\n"
      "}\n");
}

string OneofGenerator::DescriptorName(void) const {
  return variables_.find("name")->second;
}

string OneofGenerator::HasIndexAsString(void) const {
  return variables_.find("index")->second;
}

}  // namespace objectivec
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
