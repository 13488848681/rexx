
#ifndef GOOGLE_PROTOBUF_COMPILER_JAVA_LAZY_MESSAGE_FIELD_LITE_H__
#define GOOGLE_PROTOBUF_COMPILER_JAVA_LAZY_MESSAGE_FIELD_LITE_H__

#include <google/protobuf/compiler/java/java_field.h>
#include <google/protobuf/compiler/java/java_message_field_lite.h>

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

class ImmutableLazyMessageFieldLiteGenerator
    : public ImmutableMessageFieldLiteGenerator {
 public:
  explicit ImmutableLazyMessageFieldLiteGenerator(
      const FieldDescriptor* descriptor, int messageBitIndex,
      int builderBitIndex, Context* context);
  ~ImmutableLazyMessageFieldLiteGenerator();

  // overroads ImmutableMessageFieldLiteGenerator ------------------------------
  void GenerateMembers(io::Printer* printer) const;
  void GenerateBuilderMembers(io::Printer* printer) const;
  void GenerateInitializationCode(io::Printer* printer) const;
  void GenerateVisitCode(io::Printer* printer) const;
  void GenerateParsingCode(io::Printer* printer) const;
  void GenerateSerializationCode(io::Printer* printer) const;
  void GenerateSerializedSizeCode(io::Printer* printer) const;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ImmutableLazyMessageFieldLiteGenerator);
};

class ImmutableLazyMessageOneofFieldLiteGenerator
    : public ImmutableLazyMessageFieldLiteGenerator {
 public:
  ImmutableLazyMessageOneofFieldLiteGenerator(
      const FieldDescriptor* descriptor, int messageBitIndex,
      int builderBitIndex, Context* context);
  ~ImmutableLazyMessageOneofFieldLiteGenerator();

  void GenerateMembers(io::Printer* printer) const;
  void GenerateBuilderMembers(io::Printer* printer) const;
  void GenerateVisitCode(io::Printer* printer) const;
  void GenerateParsingCode(io::Printer* printer) const;
  void GenerateSerializationCode(io::Printer* printer) const;
  void GenerateSerializedSizeCode(io::Printer* printer) const;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ImmutableLazyMessageOneofFieldLiteGenerator);
};

class RepeatedImmutableLazyMessageFieldLiteGenerator
    : public RepeatedImmutableMessageFieldLiteGenerator {
 public:
  explicit RepeatedImmutableLazyMessageFieldLiteGenerator(
      const FieldDescriptor* descriptor, int messageBitIndex,
      int builderBitIndex, Context* context);
  ~RepeatedImmutableLazyMessageFieldLiteGenerator();

  // overroads RepeatedImmutableMessageFieldLiteGenerator ----------------------
  void GenerateMembers(io::Printer* printer) const;
  void GenerateBuilderMembers(io::Printer* printer) const;
  void GenerateParsingCode(io::Printer* printer) const;
  void GenerateSerializationCode(io::Printer* printer) const;
  void GenerateSerializedSizeCode(io::Printer* printer) const;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(RepeatedImmutableLazyMessageFieldLiteGenerator);
};

}  // namespace java
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_JAVA_LAZY_MESSAGE_FIELD_LITE_H__
