#ifndef GOOGLE_PROTOBUF_COMPILER_JAVA_EXTENSION_LITE_H__
#define GOOGLE_PROTOBUF_COMPILER_JAVA_EXTENSION_LITE_H__

#include <map>
#include <string>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/compiler/java/java_extension.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace java {

// Generates code for a lite extension, which may be within the scope of some
// message or may be at file scope.  This is much simpler than FieldGenerator
// since extensions are just simple identifiers with interesting types.
class ImmutableExtensionLiteGenerator : public ExtensionGenerator {
 public:
  explicit ImmutableExtensionLiteGenerator(const FieldDescriptor* descriptor,
                                           Context* context);
  virtual ~ImmutableExtensionLiteGenerator();

  virtual void Generate(io::Printer* printer);

  // Returns an estimate of the number of bytes the printed code will compile to
  virtual int GenerateNonNestedInitializationCode(io::Printer* printer);

  // Returns an estimate of the number of bytes the printed code will compile to
  virtual int GenerateRegistrationCode(io::Printer* printer);

 private:
  const FieldDescriptor* descriptor_;
  Context* context_;
  ClassNameResolver* name_resolver_;
  string scope_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ImmutableExtensionLiteGenerator);
};

}  // namespace java
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_JAVA_EXTENSION_LITE_H__
