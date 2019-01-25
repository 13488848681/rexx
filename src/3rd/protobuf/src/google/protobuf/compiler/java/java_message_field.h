
#ifndef GOOGLE_PROTOBUF_COMPILER_JAVA_MESSAGE_FIELD_H__
#define GOOGLE_PROTOBUF_COMPILER_JAVA_MESSAGE_FIELD_H__

#include <map>
#include <string>
#include <google/protobuf/compiler/java/java_field.h>

namespace google {
namespace protobuf {
  namespace compiler {
    namespace java {
      class Context;           // context.h
      class ClassNameResolver; // name_resolver.h
    }
  }
}

namespace protobuf {
namespace compiler {
namespace java {

class ImmutableMessageFieldGenerator : public ImmutableFieldGenerator {
 public:
  explicit ImmutableMessageFieldGenerator(
      const FieldDescriptor* descriptor, int messageBitIndex,
      int builderBitIndex, Context* context);
  ~ImmutableMessageFieldGenerator();

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

 protected:
  const FieldDescriptor* descriptor_;
  map<string, string> variables_;
  const int messageBitIndex_;
  const int builderBitIndex_;
  Context* context_;
  ClassNameResolver* name_resolver_;

  void PrintNestedBuilderCondition(io::Printer* printer,
      const char* regular_case, const char* nested_builder_case) const;
  void PrintNestedBuilderFunction(io::Printer* printer,
      const char* method_prototype, const char* regular_case,
      const char* nested_builder_case,
      const char* trailing_code) const;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ImmutableMessageFieldGenerator);
};

class ImmutableMessageOneofFieldGenerator
    : public ImmutableMessageFieldGenerator {
 public:
  ImmutableMessageOneofFieldGenerator(
      const FieldDescriptor* descriptor, int messageBitIndex,
      int builderBitIndex, Context* context);
  ~ImmutableMessageOneofFieldGenerator();

  void GenerateMembers(io::Printer* printer) const;
  void GenerateBuilderMembers(io::Printer* printer) const;
  void GenerateBuildingCode(io::Printer* printer) const;
  void GenerateMergingCode(io::Printer* printer) const;
  void GenerateParsingCode(io::Printer* printer) const;
  void GenerateSerializationCode(io::Printer* printer) const;
  void GenerateSerializedSizeCode(io::Printer* printer) const;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ImmutableMessageOneofFieldGenerator);
};

class RepeatedImmutableMessageFieldGenerator : public ImmutableFieldGenerator {
 public:
  explicit RepeatedImmutableMessageFieldGenerator(
      const FieldDescriptor* descriptor, int messageBitIndex,
      int builderBitIndex, Context* context);
  ~RepeatedImmutableMessageFieldGenerator();

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

 protected:
  const FieldDescriptor* descriptor_;
  map<string, string> variables_;
  const int messageBitIndex_;
  const int builderBitIndex_;
  Context* context_;
  ClassNameResolver* name_resolver_;

  void PrintNestedBuilderCondition(io::Printer* printer,
      const char* regular_case, const char* nested_builder_case) const;
  void PrintNestedBuilderFunction(io::Printer* printer,
      const char* method_prototype, const char* regular_case,
      const char* nested_builder_case,
      const char* trailing_code) const;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(RepeatedImmutableMessageFieldGenerator);
};

}  // namespace java
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_JAVA_MESSAGE_FIELD_H__
