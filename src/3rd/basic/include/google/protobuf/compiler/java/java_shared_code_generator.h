
#ifndef GOOGLE_PROTOBUF_COMPILER_JAVA_SHARED_CODE_GENERATOR_H__
#define GOOGLE_PROTOBUF_COMPILER_JAVA_SHARED_CODE_GENERATOR_H__

#include <memory>
#ifndef _SHARED_PTR_H
#include <google/protobuf/stubs/shared_ptr.h>
#endif
#include <string>
#include <vector>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/compiler/java/java_options.h>

namespace google {
namespace protobuf {
  class FileDescriptor;        // descriptor.h
  namespace compiler {
    class GeneratorContext;    // code_generator.h
    namespace java {
      class ClassNameResolver;       // name_resolver.h
    }
  }
  namespace io {
    class Printer;             // printer.h
  }
}

namespace protobuf {
namespace compiler {
namespace java {

// A generator that generates code that are shared between immutable API
// and mutable API. Currently only descriptors are shared.
class SharedCodeGenerator {
 public:
  SharedCodeGenerator(const FileDescriptor* file, const Options& options);
  ~SharedCodeGenerator();

  void Generate(GeneratorContext* generator_context, vector<string>* file_list,
                vector<string>* annotation_file_list);

  void GenerateDescriptors(io::Printer* printer);

 private:
  // Returns whether the dependency should be included in the output file.
  // Always returns true for opensource, but used internally at Google to help
  // improve compatibility with version 1 of protocol buffers.
  bool ShouldIncludeDependency(const FileDescriptor* descriptor);

  google::protobuf::scoped_ptr<ClassNameResolver> name_resolver_;
  const FileDescriptor* file_;
  const Options options_;
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(SharedCodeGenerator);
};


}  // namespace java
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_JAVA_SHARED_CODE_GENERATOR_H__
