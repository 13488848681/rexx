#ifndef GOOGLE_PROTOBUF_COMPILER_JAVA_MAP_FIELD_LITE_H__
#define GOOGLE_PROTOBUF_COMPILER_JAVA_MAP_FIELD_LITE_H__

#include <google/protobuf/compiler/java/java_field.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace java {

class ImmutableMapFieldLiteGenerator : public ImmutableFieldLiteGenerator {
 public:
  explicit ImmutableMapFieldLiteGenerator(
      const FieldDescriptor* descriptor, int messageBitIndex,
      int builderBitIndex, Context* context);
  ~ImmutableMapFieldLiteGenerator();

  // implements ImmutableFieldLiteGenerator ------------------------------------
  int GetNumBitsForMessage() const;
  int GetNumBitsForBuilder() const;
  void GenerateInterfaceMembers(io::Printer* printer) const;
  void GenerateMembers(io::Printer* printer) const;
  void GenerateBuilderMembers(io::Printer* printer) const;
  void GenerateInitializationCode(io::Printer* printer) const;
  void GenerateVisitCode(io::Printer* printer) const;
  void GenerateDynamicMethodMakeImmutableCode(io::Printer* printer) const;
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
};

}  // namespace java
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_JAVA_MAP_FIELD_LITE_H__
