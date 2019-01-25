#ifndef GOOGLE_PROTOBUF_COMPILER_CSHARP_SOURCE_GENERATOR_BASE_H__
#define GOOGLE_PROTOBUF_COMPILER_CSHARP_SOURCE_GENERATOR_BASE_H__

#include <string>

#include <google/protobuf/compiler/code_generator.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace csharp {

struct Options;

class SourceGeneratorBase {
 protected:
  SourceGeneratorBase(const FileDescriptor* descriptor, const Options* options);
  virtual ~SourceGeneratorBase();

  std::string class_access_level();
  const Options* options();

  // Write any attributes used to decorate generated function members (methods and properties).
  // Should not be used to decorate types.
  void WriteGeneratedCodeAttributes(io::Printer* printer);

 private:
  const FileDescriptor* descriptor_;
  const Options *options_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(SourceGeneratorBase);
};

}  // namespace csharp
}  // namespace compiler
}  // namespace protobuf
}  // namespace google

#endif  // GOOGLE_PROTOBUF_COMPILER_CSHARP_SOURCE_GENERATOR_BASE_H__

