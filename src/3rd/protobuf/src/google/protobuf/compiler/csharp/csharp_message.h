#ifndef GOOGLE_PROTOBUF_COMPILER_CSHARP_MESSAGE_H__
#define GOOGLE_PROTOBUF_COMPILER_CSHARP_MESSAGE_H__

#include <string>
#include <vector>

#include <google/protobuf/compiler/code_generator.h>
#include <google/protobuf/compiler/csharp/csharp_source_generator_base.h>
#include <google/protobuf/compiler/csharp/csharp_helpers.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace csharp {

class FieldGeneratorBase;

class MessageGenerator : public SourceGeneratorBase {
 public:
  MessageGenerator(const Descriptor* descriptor, const Options* options);
  ~MessageGenerator();

  void GenerateCloningCode(io::Printer* printer);
  void GenerateFreezingCode(io::Printer* printer);
  void GenerateFrameworkMethods(io::Printer* printer);
  void Generate(io::Printer* printer);

 private:
  const Descriptor* descriptor_;
  std::vector<std::string> field_names_;
  std::vector<const FieldDescriptor*> fields_by_number_;

  void GenerateMessageSerializationMethods(io::Printer* printer);
  void GenerateMergingMethods(io::Printer* printer);

  int GetFieldOrdinal(const FieldDescriptor* descriptor);
  FieldGeneratorBase* CreateFieldGeneratorInternal(
      const FieldDescriptor* descriptor);

  bool HasNestedGeneratedTypes();

  std::string class_name();
  std::string full_class_name();

  // field names sorted alphabetically
  const std::vector<std::string>& field_names();

  // field descriptors sorted by number
  const std::vector<const FieldDescriptor*>& fields_by_number();

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(MessageGenerator);
};

}  // namespace csharp
}  // namespace compiler
}  // namespace protobuf
}  // namespace google

#endif  // GOOGLE_PROTOBUF_COMPILER_CSHARP_MESSAGE_H__
