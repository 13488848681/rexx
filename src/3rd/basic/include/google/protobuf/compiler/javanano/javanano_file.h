
#ifndef GOOGLE_PROTOBUF_COMPILER_JAVANANO_FILE_H__
#define GOOGLE_PROTOBUF_COMPILER_JAVANANO_FILE_H__

#include <string>
#include <vector>
#include <google/protobuf/stubs/common.h>
#include <google/protobuf/compiler/javanano/javanano_params.h>

namespace google {
namespace protobuf {
  class FileDescriptor;        // descriptor.h
  namespace io {
    class Printer;             // printer.h
  }
  namespace compiler {
    class GeneratorContext;     // code_generator.h
  }
}

namespace protobuf {
namespace compiler {
namespace javanano {

class FileGenerator {
 public:
  explicit FileGenerator(const FileDescriptor* file, const Params& params);
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
                        GeneratorContext* output_directory,
                        vector<string>* file_list);

  const string& java_package() { return java_package_; }
  const string& classname()    { return classname_;    }

 private:
  const FileDescriptor* file_;
  const Params& params_;
  string java_package_;
  string classname_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(FileGenerator);
};

}  // namespace javanano
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_JAVANANO_FILE_H__
