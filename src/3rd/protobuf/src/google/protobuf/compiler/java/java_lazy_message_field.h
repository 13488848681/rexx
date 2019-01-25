#ifndef GOOGLE_PROTOBUF_COMPILER_JAVA_LAZY_MESSAGE_FIELD_H__
#define GOOGLE_PROTOBUF_COMPILER_JAVA_LAZY_MESSAGE_FIELD_H__

#include <google/protobuf/compiler/java/java_field.h>
#include <google/protobuf/compiler/java/java_message_field.h>

namespace google {
namespace protobuf {
  namespace compiler {
    namespace java {
      class Context;  // context.h
    }
  }
}

namespace protobuf {
namespace compiler {
namespace java {

class ImmutableLazyMessageFieldGenerator
    : public ImmutableMessageFieldGenerator {
 public:
  explicit ImmutableLazyMessageFieldGenerator(
      const FieldDescriptor* descriptor, int messageBitIndex,
      int builderBitIndex, Context* context);
  ~ImmutableLazyMessageFieldGenerator();

  // overroads ImmutableMessageFieldGenerator ---------------------------------
  void GenerateMembers(io::Printer* printer) const;
  void GenerateBuilderMembers(io::Printer* printer) const;
  void GenerateInitializationCode(io::Printer* printer) const;
  void GenerateBuilderClearCode(io::Printer* printer) const;
  void GenerateMergingCode(io::Printer* printer) const;
  void GenerateBuildingCode(io::Printer* printer) const;
  void GenerateParsingCode(io::Printer* printer) const;
  void GenerateSerializationCode(io::Printer* printer) const;
  void GenerateSerializedSizeCode(io::Printer* printer) const;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ImmutableLazyMessageFieldGenerator);
};

class ImmutableLazyMessageOneofFieldGenerator
    : public ImmutableLazyMessageFieldGenerator {
 public:
  ImmutableLazyMessageOneofFieldGenerator(
      const FieldDescriptor* descriptor, int messageBitIndex,
      int builderBitIndex, Context* context);
  ~ImmutableLazyMessageOneofFieldGenerator();

  void GenerateMembers(io::Printer* printer) const;
  void GenerateBuilderMembers(io::Printer* printer) const;
  void GenerateMergingCode(io::Printer* printer) const;
  void GenerateBuildingCode(io::Printer* printer) const;
  void GenerateParsingCode(io::Printer* printer) const;
  void GenerateSerializationCode(io::Printer* printer) const;
  void GenerateSerializedSizeCode(io::Printer* printer) const;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ImmutableLazyMessageOneofFieldGenerator);
};

class RepeatedImmutableLazyMessageFieldGenerator
    : public RepeatedImmutableMessageFieldGenerator {
 public:
  explicit RepeatedImmutableLazyMessageFieldGenerator(
      const FieldDescriptor* descriptor, int messageBitIndex,
      int builderBitIndex, Context* context);
  ~RepeatedImmutableLazyMessageFieldGenerator();

  // overroads RepeatedImmutableMessageFieldGenerator -------------------------
  void GenerateMembers(io::Printer* printer) const;
  void GenerateBuilderMembers(io::Printer* printer) const;
  void GenerateParsingCode(io::Printer* printer) const;
  void GenerateSerializationCode(io::Printer* printer) const;
  void GenerateSerializedSizeCode(io::Printer* printer) const;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(RepeatedImmutableLazyMessageFieldGenerator);
};

}  // namespace java
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_JAVA_LAZY_MESSAGE_FIELD_H__
