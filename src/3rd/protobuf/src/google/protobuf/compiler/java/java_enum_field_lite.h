#ifndef GOOGLE_PROTOBUF_COMPILER_JAVA_ENUM_FIELD_LITE_H__
#define GOOGLE_PROTOBUF_COMPILER_JAVA_ENUM_FIELD_LITE_H__

#include <map>
#include <string>
#include <google/protobuf/compiler/java/java_field.h>

namespace google {
namespace protobuf {
  namespace compiler {
    namespace java {
      class Context;            // context.h
      class ClassNameResolver;  // name_resolver.h
    }
  }
}

namespace protobuf {
namespace compiler {
namespace java {

class ImmutableEnumFieldLiteGenerator : public ImmutableFieldLiteGenerator {
 public:
  explicit ImmutableEnumFieldLiteGenerator(
      const FieldDescriptor* descriptor, int messageBitIndex,
      int builderBitIndex, Context* context);
  ~ImmutableEnumFieldLiteGenerator();

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

 protected:
  const FieldDescriptor* descriptor_;
  map<string, string> variables_;
  const int messageBitIndex_;
  const int builderBitIndex_;
  Context* context_;
  ClassNameResolver* name_resolver_;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ImmutableEnumFieldLiteGenerator);
};

class ImmutableEnumOneofFieldLiteGenerator
    : public ImmutableEnumFieldLiteGenerator {
 public:
  ImmutableEnumOneofFieldLiteGenerator(
      const FieldDescriptor* descriptor, int messageBitIndex,
      int builderBitIndex, Context* context);
  ~ImmutableEnumOneofFieldLiteGenerator();

  void GenerateMembers(io::Printer* printer) const;
  void GenerateBuilderMembers(io::Printer* printer) const;
  void GenerateVisitCode(io::Printer* printer) const;
  void GenerateParsingCode(io::Printer* printer) const;
  void GenerateSerializationCode(io::Printer* printer) const;
  void GenerateSerializedSizeCode(io::Printer* printer) const;
  void GenerateEqualsCode(io::Printer* printer) const;
  void GenerateHashCode(io::Printer* printer) const;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ImmutableEnumOneofFieldLiteGenerator);
};

class RepeatedImmutableEnumFieldLiteGenerator
    : public ImmutableFieldLiteGenerator {
 public:
  explicit RepeatedImmutableEnumFieldLiteGenerator(
      const FieldDescriptor* descriptor, int messageBitIndex,
      int builderBitIndex, Context* context);
  ~RepeatedImmutableEnumFieldLiteGenerator();

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

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(RepeatedImmutableEnumFieldLiteGenerator);
};

}  // namespace java
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_JAVA_ENUM_FIELD_LITE_H__
