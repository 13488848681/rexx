
#ifndef GOOGLE_PROTOBUF_COMPILER_JAVA_MESSAGE_LITE_H__
#define GOOGLE_PROTOBUF_COMPILER_JAVA_MESSAGE_LITE_H__

#include <string>
#include <map>
#include <google/protobuf/compiler/java/java_field.h>
#include <google/protobuf/compiler/java/java_message.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace java {

class ImmutableMessageLiteGenerator : public MessageGenerator {
 public:
  ImmutableMessageLiteGenerator(const Descriptor* descriptor, Context* context);
  virtual ~ImmutableMessageLiteGenerator();

  virtual void Generate(io::Printer* printer);
  virtual void GenerateInterface(io::Printer* printer);
  virtual void GenerateExtensionRegistrationCode(io::Printer* printer);
  virtual void GenerateStaticVariables(
      io::Printer* printer, int* bytecode_estimate);
  virtual int GenerateStaticVariableInitializers(io::Printer* printer);

 private:

  void GenerateMessageSerializationMethods(io::Printer* printer);
  void GenerateParseFromMethods(io::Printer* printer);
  void GenerateSerializeOneField(io::Printer* printer,
                                 const FieldDescriptor* field);
  void GenerateSerializeOneExtensionRange(
      io::Printer* printer, const Descriptor::ExtensionRange* range);

  void GenerateBuilder(io::Printer* printer);
  void GenerateDynamicMethodIsInitialized(io::Printer* printer);
  void GenerateDynamicMethodMakeImmutable(io::Printer* printer);
  void GenerateDynamicMethodVisit(io::Printer* printer);
  void GenerateDynamicMethodMergeFromStream(io::Printer* printer);
  void GenerateDynamicMethodNewBuilder(io::Printer* printer);
  void GenerateInitializers(io::Printer* printer);
  void GenerateEqualsAndHashCode(io::Printer* printer);
  void GenerateParser(io::Printer* printer);
  void GenerateConstructor(io::Printer* printer);

  Context* context_;
  ClassNameResolver* name_resolver_;
  FieldGeneratorMap<ImmutableFieldLiteGenerator> field_generators_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ImmutableMessageLiteGenerator);
};

}  // namespace java
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_JAVA_MESSAGE_LITE_H__
