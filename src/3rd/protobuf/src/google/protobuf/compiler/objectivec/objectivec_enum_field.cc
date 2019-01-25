
#include <map>
#include <string>

#include <google/protobuf/compiler/objectivec/objectivec_enum_field.h>
#include <google/protobuf/stubs/common.h>
#include <google/protobuf/compiler/objectivec/objectivec_helpers.h>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/wire_format.h>
#include <google/protobuf/stubs/strutil.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace objectivec {

namespace {

void SetEnumVariables(const FieldDescriptor* descriptor,
                      map<string, string>* variables) {
  string type = EnumName(descriptor->enum_type());
  (*variables)["storage_type"] = type;
  // For non repeated fields, if it was defined in a different file, the
  // property decls need to use "enum NAME" rather than just "NAME" to support
  // the forward declaration of the enums.
  if (!descriptor->is_repeated() &&
      (descriptor->file() != descriptor->enum_type()->file())) {
    (*variables)["property_type"] = "enum " + type;
  }
  (*variables)["enum_verifier"] = type + "_IsValidValue";
  (*variables)["enum_desc_func"] = type + "_EnumDescriptor";

  (*variables)["dataTypeSpecific_name"] = "enumDescFunc";
  (*variables)["dataTypeSpecific_value"] = (*variables)["enum_desc_func"];

  const Descriptor* msg_descriptor = descriptor->containing_type();
  (*variables)["owning_message_class"] = ClassName(msg_descriptor);
}
}  // namespace

EnumFieldGenerator::EnumFieldGenerator(const FieldDescriptor* descriptor,
                                       const Options& options)
    : SingleFieldGenerator(descriptor, options) {
  SetEnumVariables(descriptor, &variables_);
}

EnumFieldGenerator::~EnumFieldGenerator() {}

void EnumFieldGenerator::GenerateCFunctionDeclarations(
    io::Printer* printer) const {
  if (!HasPreservingUnknownEnumSemantics(descriptor_->file())) {
    return;
  }

  printer->Print(
      variables_,
      "/**\n"
      " * Fetches the raw value of a @c $owning_message_class$'s @c $name$ property, even\n"
      " * if the value was not defined by the enum at the time the code was generated.\n"
      " **/\n"
      "int32_t $owning_message_class$_$capitalized_name$_RawValue($owning_message_class$ *message);\n"
      "/**\n"
      " * Sets the raw value of an @c $owning_message_class$'s @c $name$ property, allowing\n"
      " * it to be set to a value that was not defined by the enum at the time the code\n"
      " * was generated.\n"
      " **/\n"
      "void Set$owning_message_class$_$capitalized_name$_RawValue($owning_message_class$ *message, int32_t value);\n"
      "\n");
}

void EnumFieldGenerator::GenerateCFunctionImplementations(
    io::Printer* printer) const {
  if (!HasPreservingUnknownEnumSemantics(descriptor_->file())) return;

  printer->Print(
      variables_,
      "int32_t $owning_message_class$_$capitalized_name$_RawValue($owning_message_class$ *message) {\n"
      "  GPBDescriptor *descriptor = [$owning_message_class$ descriptor];\n"
      "  GPBFieldDescriptor *field = [descriptor fieldWithNumber:$field_number_name$];\n"
      "  return GPBGetMessageInt32Field(message, field);\n"
      "}\n"
      "\n"
      "void Set$owning_message_class$_$capitalized_name$_RawValue($owning_message_class$ *message, int32_t value) {\n"
      "  GPBDescriptor *descriptor = [$owning_message_class$ descriptor];\n"
      "  GPBFieldDescriptor *field = [descriptor fieldWithNumber:$field_number_name$];\n"
      "  GPBSetInt32IvarWithFieldInternal(message, field, value, descriptor.file.syntax);\n"
      "}\n"
      "\n");
}

void EnumFieldGenerator::DetermineForwardDeclarations(
    set<string>* fwd_decls) const {
  SingleFieldGenerator::DetermineForwardDeclarations(fwd_decls);
  // If it is an enum defined in a different file, then we'll need a forward
  // declaration for it.  When it is in our file, all the enums are output
  // before the message, so it will be declared before it is needed.
  if (descriptor_->file() != descriptor_->enum_type()->file()) {
    // Enum name is already in "storage_type".
    const string& name = variable("storage_type");
    fwd_decls->insert("GPB_ENUM_FWD_DECLARE(" + name + ")");
  }
}

RepeatedEnumFieldGenerator::RepeatedEnumFieldGenerator(
    const FieldDescriptor* descriptor, const Options& options)
    : RepeatedFieldGenerator(descriptor, options) {
  SetEnumVariables(descriptor, &variables_);
  variables_["array_storage_type"] = "GPBEnumArray";
}

RepeatedEnumFieldGenerator::~RepeatedEnumFieldGenerator() {}

void RepeatedEnumFieldGenerator::FinishInitialization(void) {
  RepeatedFieldGenerator::FinishInitialization();
  variables_["array_comment"] =
      "// |" + variables_["name"] + "| contains |" + variables_["storage_type"] + "|\n";
}

}  // namespace objectivec
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
