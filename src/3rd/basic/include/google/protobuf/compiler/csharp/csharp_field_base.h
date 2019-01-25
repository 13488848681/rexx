
#ifndef GOOGLE_PROTOBUF_COMPILER_CSHARP_FIELD_BASE_H__
#define GOOGLE_PROTOBUF_COMPILER_CSHARP_FIELD_BASE_H__

#include <string>
#include <google/protobuf/stubs/strutil.h>

#include <google/protobuf/compiler/code_generator.h>
#include <google/protobuf/compiler/csharp/csharp_source_generator_base.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace csharp {

class FieldGeneratorBase : public SourceGeneratorBase {
 public:
  FieldGeneratorBase(const FieldDescriptor* descriptor,
                     int fieldOrdinal,
                     const Options* options);
  ~FieldGeneratorBase();

  virtual void GenerateCloningCode(io::Printer* printer) = 0;
  virtual void GenerateFreezingCode(io::Printer* printer);
  virtual void GenerateCodecCode(io::Printer* printer);
  virtual void GenerateMembers(io::Printer* printer) = 0;
  virtual void GenerateMergingCode(io::Printer* printer) = 0;
  virtual void GenerateParsingCode(io::Printer* printer) = 0;
  virtual void GenerateSerializationCode(io::Printer* printer) = 0;
  virtual void GenerateSerializedSizeCode(io::Printer* printer) = 0;

  virtual void WriteHash(io::Printer* printer) = 0;
  virtual void WriteEquals(io::Printer* printer) = 0;
  // Currently unused, as we use reflection to generate JSON
  virtual void WriteToString(io::Printer* printer) = 0;

 protected:
  const FieldDescriptor* descriptor_;
  const int fieldOrdinal_;
  map<string, string> variables_;

  void AddDeprecatedFlag(io::Printer* printer);
  void AddNullCheck(io::Printer* printer);
  void AddNullCheck(io::Printer* printer, const std::string& name);

  void AddPublicMemberAttributes(io::Printer* printer);
  void SetCommonOneofFieldVariables(map<string, string>* variables);

  std::string oneof_property_name();
  std::string oneof_name();
  std::string property_name();
  std::string name();
  std::string type_name();
  std::string type_name(const FieldDescriptor* descriptor);
  bool has_default_value();
  bool is_nullable_type();
  std::string default_value();
  std::string default_value(const FieldDescriptor* descriptor);
  std::string number();
  std::string capitalized_type_name();

 private:
  void SetCommonFieldVariables(map<string, string>* variables);
  std::string GetStringDefaultValueInternal();
  std::string GetBytesDefaultValueInternal();

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(FieldGeneratorBase);
};

}  // namespace csharp
}  // namespace compiler
}  // namespace protobuf
}  // namespace google

#endif  // GOOGLE_PROTOBUF_COMPILER_CSHARP_FIELD_BASE_H__

