
#ifndef GOOGLE_PROTOBUF_COMPILER_JAVA_PRIMITIVE_FIELD_LITE_H__
#define GOOGLE_PROTOBUF_COMPILER_JAVA_PRIMITIVE_FIELD_LITE_H__

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

class ImmutablePrimitiveFieldLiteGenerator
    : public ImmutableFieldLiteGenerator {
 public:
  explicit ImmutablePrimitiveFieldLiteGenerator(
      const FieldDescriptor* descriptor, int messageBitIndex,
      int builderBitIndex, Context* context);
  ~ImmutablePrimitiveFieldLiteGenerator();

  // implements ImmutableFieldLiteGenerator ------------------------------------
  int GetNumBitsForMessage() const;
  int GetNumBitsForBuilder() const;
  void GenerateInterfaceMembers(io::Printer* printer) const;
  void GenerateMembers(io::Printer* printer) const;
  void GenerateBuilderMembers(io::Printer* printer) const;
  void GenerateInitializationCode(io::Printer* printer) const;
  void GenerateBuilderClearCode(io::Printer* printer) const;
  void GenerateVisitCode(io::Printer* printer) const;
  void GenerateBuildingCode(io::Printer* printer) const;
  void GenerateDynamicMethodMakeImmutableCode(io::Printer* printer) const;
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

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ImmutablePrimitiveFieldLiteGenerator);
};

class ImmutablePrimitiveOneofFieldLiteGenerator
    : public ImmutablePrimitiveFieldLiteGenerator {
 public:
  ImmutablePrimitiveOneofFieldLiteGenerator(
      const FieldDescriptor* descriptor, int messageBitIndex,
      int builderBitIndex, Context* context);
  ~ImmutablePrimitiveOneofFieldLiteGenerator();

  void GenerateMembers(io::Printer* printer) const;
  void GenerateBuilderMembers(io::Printer* printer) const;
  void GenerateBuildingCode(io::Printer* printer) const;
  void GenerateVisitCode(io::Printer* printer) const;
  void GenerateParsingCode(io::Printer* printer) const;
  void GenerateSerializationCode(io::Printer* printer) const;
  void GenerateSerializedSizeCode(io::Printer* printer) const;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ImmutablePrimitiveOneofFieldLiteGenerator);
};

class RepeatedImmutablePrimitiveFieldLiteGenerator
    : public ImmutableFieldLiteGenerator {
 public:
  explicit RepeatedImmutablePrimitiveFieldLiteGenerator(
      const FieldDescriptor* descriptor, int messageBitIndex,
      int builderBitIndex, Context* context);
  virtual ~RepeatedImmutablePrimitiveFieldLiteGenerator();

  // implements ImmutableFieldLiteGenerator ------------------------------------
  int GetNumBitsForMessage() const;
  int GetNumBitsForBuilder() const;
  void GenerateInterfaceMembers(io::Printer* printer) const;
  void GenerateMembers(io::Printer* printer) const;
  void GenerateBuilderMembers(io::Printer* printer) const;
  void GenerateInitializationCode(io::Printer* printer) const;
  void GenerateBuilderClearCode(io::Printer* printer) const;
  void GenerateVisitCode(io::Printer* printer) const;
  void GenerateBuildingCode(io::Printer* printer) const;
  void GenerateDynamicMethodMakeImmutableCode(io::Printer* printer) const;
  void GenerateParsingCode(io::Printer* printer) const;
  void GenerateParsingCodeFromPacked(io::Printer* printer) const;
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
  const int messageBitIndex_;
  const int builderBitIndex_;
  Context* context_;
  ClassNameResolver* name_resolver_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(RepeatedImmutablePrimitiveFieldLiteGenerator);
};

}  // namespace java
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_JAVA_PRIMITIVE_FIELD_LITE_H__
