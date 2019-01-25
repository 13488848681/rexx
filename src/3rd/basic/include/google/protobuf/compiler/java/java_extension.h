
#ifndef GOOGLE_PROTOBUF_COMPILER_JAVA_EXTENSION_H__
#define GOOGLE_PROTOBUF_COMPILER_JAVA_EXTENSION_H__

#include <map>
#include <string>

#include <google/protobuf/stubs/common.h>

namespace google {
namespace protobuf {
  class FieldDescriptor;       // descriptor.h
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

// Generates code for an extension, which may be within the scope of some
// message or may be at file scope.  This is much simpler than FieldGenerator
// since extensions are just simple identifiers with interesting types.
class ExtensionGenerator {
 public:
  explicit ExtensionGenerator() {}
  virtual ~ExtensionGenerator() {}

  virtual void Generate(io::Printer* printer) = 0;

  // Returns an estimate of the number of bytes the printed code will compile to
  virtual int GenerateNonNestedInitializationCode(io::Printer* printer) = 0;

  // Returns an estimate of the number of bytes the printed code will compile to
  virtual int GenerateRegistrationCode(io::Printer* printer) = 0;

 protected:
  static void InitTemplateVars(const FieldDescriptor* descriptor,
                               const string& scope,
                               bool immutable,
                               ClassNameResolver* name_resolver,
                               map<string, string>* vars_pointer);

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ExtensionGenerator);
};

class ImmutableExtensionGenerator : public ExtensionGenerator {
 public:
  explicit ImmutableExtensionGenerator(const FieldDescriptor* descriptor,
                                       Context* context);
  virtual ~ImmutableExtensionGenerator();

  virtual void Generate(io::Printer* printer);
  virtual int GenerateNonNestedInitializationCode(io::Printer* printer);
  virtual int GenerateRegistrationCode(io::Printer* printer);

 protected:
  const FieldDescriptor* descriptor_;
  Context* context_;
  ClassNameResolver* name_resolver_;
  string scope_;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ImmutableExtensionGenerator);
};

}  // namespace java
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_JAVA_EXTENSION_H__
