
#include <map>
#include <string>

#include <google/protobuf/compiler/objectivec/objectivec_message_field.h>
#include <google/protobuf/compiler/objectivec/objectivec_helpers.h>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/wire_format.h>
#include <google/protobuf/stubs/strutil.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace objectivec {

namespace {

void SetMessageVariables(const FieldDescriptor* descriptor,
                         map<string, string>* variables) {
  const string& message_type = ClassName(descriptor->message_type());
  (*variables)["type"] = message_type;
  (*variables)["containing_class"] = ClassName(descriptor->containing_type());
  (*variables)["storage_type"] = message_type;
  (*variables)["group_or_message"] =
      (descriptor->type() == FieldDescriptor::TYPE_GROUP) ? "Group" : "Message";

  (*variables)["dataTypeSpecific_value"] = "GPBStringifySymbol(" + message_type + ")";
}

}  // namespace

MessageFieldGenerator::MessageFieldGenerator(const FieldDescriptor* descriptor,
                                             const Options& options)
    : ObjCObjFieldGenerator(descriptor, options) {
  SetMessageVariables(descriptor, &variables_);
}

MessageFieldGenerator::~MessageFieldGenerator() {}

void MessageFieldGenerator::DetermineForwardDeclarations(
    set<string>* fwd_decls) const {
  ObjCObjFieldGenerator::DetermineForwardDeclarations(fwd_decls);
  // Class name is already in "storage_type".
  fwd_decls->insert("@class " + variable("storage_type"));
}

bool MessageFieldGenerator::WantsHasProperty(void) const {
  if (descriptor_->containing_oneof() != NULL) {
    // If in a oneof, it uses the oneofcase instead of a has bit.
    return false;
  }
  // In both proto2 & proto3, message fields have a has* property to tell
  // when it is a non default value.
  return true;
}

RepeatedMessageFieldGenerator::RepeatedMessageFieldGenerator(
    const FieldDescriptor* descriptor, const Options& options)
    : RepeatedFieldGenerator(descriptor, options) {
  SetMessageVariables(descriptor, &variables_);
  variables_["array_storage_type"] = "NSMutableArray";
  variables_["array_property_type"] =
      "NSMutableArray<" + variables_["storage_type"] + "*>";
}

RepeatedMessageFieldGenerator::~RepeatedMessageFieldGenerator() {}

void RepeatedMessageFieldGenerator::DetermineForwardDeclarations(
    set<string>* fwd_decls) const {
  RepeatedFieldGenerator::DetermineForwardDeclarations(fwd_decls);
  // Class name is already in "storage_type".
  fwd_decls->insert("@class " + variable("storage_type"));
}


}  // namespace objectivec
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
