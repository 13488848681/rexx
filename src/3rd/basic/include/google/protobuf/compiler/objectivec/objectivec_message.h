
#ifndef GOOGLE_PROTOBUF_COMPILER_OBJECTIVEC_MESSAGE_H__
#define GOOGLE_PROTOBUF_COMPILER_OBJECTIVEC_MESSAGE_H__

#include <string>
#include <set>
#include <vector>
#include <google/protobuf/compiler/objectivec/objectivec_field.h>
#include <google/protobuf/compiler/objectivec/objectivec_helpers.h>
#include <google/protobuf/compiler/objectivec/objectivec_oneof.h>
#include <google/protobuf/stubs/common.h>

namespace google {
namespace protobuf {

namespace io {
class Printer;  // printer.h
}  // namespace io

namespace compiler {
namespace objectivec {

class ExtensionGenerator;
class EnumGenerator;

class MessageGenerator {
 public:
  MessageGenerator(const string& root_classname,
                   const Descriptor* descriptor,
                   const Options& options);
  ~MessageGenerator();

  void GenerateStaticVariablesInitialization(io::Printer* printer);
  void GenerateEnumHeader(io::Printer* printer);
  void GenerateMessageHeader(io::Printer* printer);
  void GenerateSource(io::Printer* printer);
  void GenerateExtensionRegistrationSource(io::Printer* printer);
  void DetermineForwardDeclarations(set<string>* fwd_decls);

  // Checks if the message or a nested message includes a oneof definition.
  bool IncludesOneOfDefinition() const;

 private:
  void GenerateParseFromMethodsHeader(io::Printer* printer);

  void GenerateSerializeOneFieldSource(io::Printer* printer,
                                       const FieldDescriptor* field);
  void GenerateSerializeOneExtensionRangeSource(
      io::Printer* printer, const Descriptor::ExtensionRange* range);

  void GenerateMessageDescriptionSource(io::Printer* printer);
  void GenerateDescriptionOneFieldSource(io::Printer* printer,
                                         const FieldDescriptor* field);

  const string root_classname_;
  const Descriptor* descriptor_;
  FieldGeneratorMap field_generators_;
  const string class_name_;
  vector<ExtensionGenerator*> extension_generators_;
  vector<EnumGenerator*> enum_generators_;
  vector<MessageGenerator*> nested_message_generators_;
  vector<OneofGenerator*> oneof_generators_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(MessageGenerator);
};
}  // namespace objectivec
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_OBJECTIVEC_MESSAGE_H__
