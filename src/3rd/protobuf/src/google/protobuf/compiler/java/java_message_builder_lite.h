
#ifndef GOOGLE_PROTOBUF_COMPILER_JAVA_MESSAGE_BUILDER_LITE_H__
#define GOOGLE_PROTOBUF_COMPILER_JAVA_MESSAGE_BUILDER_LITE_H__

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

class MessageBuilderLiteGenerator {
 public:
  explicit MessageBuilderLiteGenerator(const Descriptor* descriptor,
                                   Context* context);
  virtual ~MessageBuilderLiteGenerator();

  virtual void Generate(io::Printer* printer);

 private:
  void GenerateCommonBuilderMethods(io::Printer* printer);

  const Descriptor* descriptor_;
  Context* context_;
  ClassNameResolver* name_resolver_;
  FieldGeneratorMap<ImmutableFieldLiteGenerator> field_generators_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(MessageBuilderLiteGenerator);
};

}  // namespace java
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_JAVA_MESSAGE_BUILDER_LITE_H__
