#ifndef GOOGLE_PROTOBUF_COMPILER_JAVA_MESSAGE_BUILDER_H__
#define GOOGLE_PROTOBUF_COMPILER_JAVA_MESSAGE_BUILDER_H__

#include <string>
#include <map>
#include <google/protobuf/compiler/java/java_field.h>

namespace google {
namespace protobuf {
  namespace compiler {
    namespace java {
      class Context;           // context.h
      class ClassNameResolver; // name_resolver.h
    }
  }
  namespace io {
    class Printer;             // printer.h
  }
}

namespace protobuf {
namespace compiler {
namespace java {

class MessageBuilderGenerator {
 public:
  explicit MessageBuilderGenerator(const Descriptor* descriptor,
                                   Context* context);
  virtual ~MessageBuilderGenerator();

  virtual void Generate(io::Printer* printer);

 private:
  void GenerateCommonBuilderMethods(io::Printer* printer);
  void GenerateDescriptorMethods(io::Printer* printer);
  void GenerateBuilderParsingMethods(io::Printer* printer);
  void GenerateIsInitialized(io::Printer* printer);

  const Descriptor* descriptor_;
  Context* context_;
  ClassNameResolver* name_resolver_;
  FieldGeneratorMap<ImmutableFieldGenerator> field_generators_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(MessageBuilderGenerator);
};

}  // namespace java
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_JAVA_MESSAGE_BUILDER_H__
