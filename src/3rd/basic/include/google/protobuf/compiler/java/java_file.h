
#ifndef GOOGLE_PROTOBUF_COMPILER_JAVA_FILE_H__
#define GOOGLE_PROTOBUF_COMPILER_JAVA_FILE_H__

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
  class FileDescriptor;          // descriptor.h
  namespace io {
    class Printer;               // printer.h
  }
  namespace compiler {
    class GeneratorContext;      // code_generator.h
    namespace java {
      class Context;             // context.h
      class MessageGenerator;    // message.h
      class GeneratorFactory;    // generator_factory.h
      class ExtensionGenerator;  // extension.h
      class ClassNameResolver;   // name_resolver.h
    }
  }
}

namespace protobuf {
namespace compiler {
namespace java {

class FileGenerator {
 public:
  FileGenerator(const FileDescriptor* file, const Options& options,
                bool immutable_api = true);
  ~FileGenerator();

  // Checks for problems that would otherwise lead to cryptic compile errors.
  // Returns true if there are no problems, or writes an error description to
  // the given string and returns false otherwise.
  bool Validate(string* error);

  void Generate(io::Printer* printer);

  // If we aren't putting everything into one file, this will write all the
  // files other than the outer file (i.e. one for each message, enum, and
  // service type).
  void GenerateSiblings(const string& package_dir,
                        GeneratorContext* generator_context,
                        vector<string>* file_list,
                        vector<string>* annotation_list);

  const string& java_package() { return java_package_; }
  const string& classname()    { return classname_;    }

 private:
  void GenerateDescriptorInitializationCodeForImmutable(io::Printer* printer);
  void GenerateDescriptorInitializationCodeForMutable(io::Printer* printer);

  bool ShouldIncludeDependency(const FileDescriptor* descriptor,
                               bool immutable_api_);

  const FileDescriptor* file_;
  string java_package_;
  string classname_;

  google::protobuf::scoped_array<google::protobuf::scoped_ptr<MessageGenerator> > message_generators_;
  google::protobuf::scoped_array<google::protobuf::scoped_ptr<ExtensionGenerator> > extension_generators_;
  google::protobuf::scoped_ptr<GeneratorFactory> generator_factory_;
  google::protobuf::scoped_ptr<Context> context_;
  ClassNameResolver* name_resolver_;
  const Options options_;
  bool immutable_api_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(FileGenerator);
};

}  // namespace java
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_JAVA_FILE_H__
