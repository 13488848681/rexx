#ifndef GOOGLE_PROTOBUF_COMPILER_JAVA_MAP_FIELD_H__
#define GOOGLE_PROTOBUF_COMPILER_JAVA_MAP_FIELD_H__

#include <google/protobuf/compiler/java/java_field.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace java {

class ImmutableMapFieldGenerator : public ImmutableFieldGenerator {
 public:
  explicit ImmutableMapFieldGenerator(
      const FieldDescriptor* descriptor, int messageBitIndex,
      int builderBitIndex, Context* context);
  ~ImmutableMapFieldGenerator();

  // implements ImmutableFieldGenerator ---------------------------------------
  int GetNumBitsForMessage() const;
  int GetNumBitsForBuilder() const;
  void GenerateInterfaceMembers(io::Printer* printer) const;
  void GenerateMembers(io::Printer* printer) const;
  void GenerateBuilderMembers(io::Printer* printer) const;
  void GenerateInitializationCode(io::Printer* printer) const;
  void GenerateBuilderClearCode(io::Printer* printer) const;
  void GenerateMergingCode(io::Printer* printer) const;
  void GenerateBuildingCode(io::Printer* printer) const;
  void GenerateParsingCode(io::Printer* printer) const;
  void GenerateParsingDoneCode(io::Printer* printer) const;
  void GenerateSerializationCode(io::Printer* printer) const;
  void GenerateSerializedSizeCode(io::Printer* printer) const;
  void GenerateFieldBuilderInitializationCode(io::Printer* printer) const;
  void GenerateEqualsCode(io::Printer* printer) const;
  void GenerateHashCode(io::Printer* printer) const;

  string GetBoxedType() const;

 private:
  const FieldDescriptor* descriptor_;
  map<string, string> variables_;
  ClassNameResolver* name_resolver_;
  void GenerateMapGetters(io::Printer* printer) const;
};

}  // namespace java
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_JAVA_MAP_FIELD_H__
