
#ifndef GOOGLE_PROTOBUF_COMPILER_JAVANANO_NANO_GENERATOR_H__
#define GOOGLE_PROTOBUF_COMPILER_JAVANANO_NANO_GENERATOR_H__

#include <string>
#include <google/protobuf/compiler/code_generator.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace javanano {

// CodeGenerator implementation which generates Java nano code.  If you create your
// own protocol compiler binary and you want it to support Java output for the
// nano runtime, you can do so by registering an instance of this CodeGenerator with
// the CommandLineInterface in your main() function.
class LIBPROTOC_EXPORT JavaNanoGenerator : public CodeGenerator {
 public:
  JavaNanoGenerator();
  ~JavaNanoGenerator();

  // implements CodeGenerator ----------------------------------------
  bool Generate(const FileDescriptor* file,
                const string& parameter,
                GeneratorContext* output_directory,
                string* error) const;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(JavaNanoGenerator);
};

}  // namespace javanano
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_JAVANANO_NANO_GENERATOR_H__
