
#ifndef GOOGLE_PROTOBUF_COMPILER_OBJECTIVEC_GENERATOR_H__
#define GOOGLE_PROTOBUF_COMPILER_OBJECTIVEC_GENERATOR_H__

#include <string>
#include <google/protobuf/compiler/code_generator.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace objectivec {

// CodeGenerator implementation which generates a ObjectiveC source file and
// header.  If you create your own protocol compiler binary and you want it to
// support ObjectiveC output, you can do so by registering an instance of this
// CodeGenerator with the CommandLineInterface in your main() function.
class LIBPROTOC_EXPORT ObjectiveCGenerator : public CodeGenerator {
 public:
  ObjectiveCGenerator();
  ~ObjectiveCGenerator();

  // implements CodeGenerator ----------------------------------------
  bool Generate(const FileDescriptor* file, const string& parameter,
                OutputDirectory* output_directory, string* error) const;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ObjectiveCGenerator);
};

}  // namespace objectivec
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_OBJECTIVEC_GENERATOR_H__
