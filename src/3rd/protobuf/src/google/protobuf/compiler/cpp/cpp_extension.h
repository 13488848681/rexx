#ifndef GOOGLE_PROTOBUF_COMPILER_CPP_EXTENSION_H__
#define GOOGLE_PROTOBUF_COMPILER_CPP_EXTENSION_H__

#include <string>
#include <google/protobuf/stubs/common.h>
#include <google/protobuf/compiler/cpp/cpp_options.h>

namespace google {
namespace protobuf {
  class FieldDescriptor;       // descriptor.h
  namespace io {
    class Printer;             // printer.h
  }
}

namespace protobuf {
namespace compiler {
namespace cpp {

// Generates code for an extension, which may be within the scope of some
// message or may be at file scope.  This is much simpler than FieldGenerator
// since extensions are just simple identifiers with interesting types.
class ExtensionGenerator {
 public:
  // See generator.cc for the meaning of dllexport_decl.
  explicit ExtensionGenerator(const FieldDescriptor* descriptor,
                              const Options& options);
  ~ExtensionGenerator();

  // Header stuff.
  void GenerateDeclaration(io::Printer* printer);

  // Source file stuff.
  void GenerateDefinition(io::Printer* printer);

  // Generate code to register the extension.
  void GenerateRegistration(io::Printer* printer);

 private:
  const FieldDescriptor* descriptor_;
  string type_traits_;
  Options options_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ExtensionGenerator);
};

}  // namespace cpp
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_CPP_MESSAGE_H__
