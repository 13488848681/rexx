#ifndef GOOGLE_PROTOBUF_COMPILER_JAVA_GENERATOR_H__
#define GOOGLE_PROTOBUF_COMPILER_JAVA_GENERATOR_H__

#include <string>
#include <google/protobuf/compiler/code_generator.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace java {

// CodeGenerator implementation which generates Java code.  If you create your
// own protocol compiler binary and you want it to support Java output, you
// can do so by registering an instance of this CodeGenerator with the
// CommandLineInterface in your main() function.
class LIBPROTOC_EXPORT JavaGenerator : public CodeGenerator {
 public:
  JavaGenerator();
  ~JavaGenerator();

  // implements CodeGenerator ----------------------------------------
  bool Generate(const FileDescriptor* file,
                const string& parameter,
                GeneratorContext* context,
                string* error) const;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(JavaGenerator);
};

}  // namespace java
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_JAVA_GENERATOR_H__
