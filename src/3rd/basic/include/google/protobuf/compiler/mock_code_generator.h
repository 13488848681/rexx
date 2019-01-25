
#ifndef GOOGLE_PROTOBUF_COMPILER_MOCK_CODE_GENERATOR_H__
#define GOOGLE_PROTOBUF_COMPILER_MOCK_CODE_GENERATOR_H__

#include <string>

#include <google/protobuf/compiler/code_generator.h>

namespace google {
namespace protobuf {
class FileDescriptor;
}  // namespace protobuf

namespace protobuf {
namespace compiler {


class MockCodeGenerator : public CodeGenerator {
 public:
  MockCodeGenerator(const string& name);
  virtual ~MockCodeGenerator();

  // Expect (via gTest) that a MockCodeGenerator with the given name was called
  // with the given parameters by inspecting the output location.
  //
  // |insertions| is a comma-separated list of names of MockCodeGenerators which
  // should have inserted lines into this file.
  // |parsed_file_list| is a comma-separated list of names of the files
  // that are being compiled together in this run.
  static void ExpectGenerated(const string& name,
                              const string& parameter,
                              const string& insertions,
                              const string& file,
                              const string& first_message_name,
                              const string& parsed_file_list,
                              const string& output_directory);

  // Get the name of the file which would be written by the given generator.
  static string GetOutputFileName(const string& generator_name,
                                  const FileDescriptor* file);
  static string GetOutputFileName(const string& generator_name,
                                  const string& file);

  // implements CodeGenerator ----------------------------------------

  virtual bool Generate(const FileDescriptor* file,
                        const string& parameter,
                        GeneratorContext* context,
                        string* error) const;

 private:
  string name_;

  static string GetOutputFileContent(const string& generator_name,
                                     const string& parameter,
                                     const FileDescriptor* file,
                                     GeneratorContext *context);
  static string GetOutputFileContent(const string& generator_name,
                                     const string& parameter,
                                     const string& file,
                                     const string& parsed_file_list,
                                     const string& first_message_name);
};

}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_MOCK_CODE_GENERATOR_H__
