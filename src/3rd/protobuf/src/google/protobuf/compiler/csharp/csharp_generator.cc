#include <sstream>

#include <google/protobuf/compiler/code_generator.h>
#include <google/protobuf/compiler/plugin.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/stubs/strutil.h>

#include <google/protobuf/compiler/csharp/csharp_generator.h>
#include <google/protobuf/compiler/csharp/csharp_helpers.h>
#include <google/protobuf/compiler/csharp/csharp_names.h>
#include <google/protobuf/compiler/csharp/csharp_options.h>
#include <google/protobuf/compiler/csharp/csharp_reflection_class.h>

using google::protobuf::internal::scoped_ptr;

namespace google {
namespace protobuf {
namespace compiler {
namespace csharp {

void GenerateFile(const google::protobuf::FileDescriptor* file,
                  io::Printer* printer,
                  const Options* options) {
  ReflectionClassGenerator reflectionClassGenerator(file, options);
  reflectionClassGenerator.Generate(printer);
}

bool Generator::Generate(
    const FileDescriptor* file,
    const string& parameter,
    GeneratorContext* generator_context,
    string* error) const {

  vector<pair<string, string> > options;
  ParseGeneratorParameter(parameter, &options);

  // We only support proto3 - but we make an exception for descriptor.proto.
  if (file->syntax() != FileDescriptor::SYNTAX_PROTO3 && !IsDescriptorProto(file)) {
    *error = "C# code generation only supports proto3 syntax";
    return false;
  }

  struct Options cli_options;

  for (int i = 0; i < options.size(); i++) {
    if (options[i].first == "file_extension") {
      cli_options.file_extension = options[i].second;
    } else if (options[i].first == "base_namespace") {
      cli_options.base_namespace = options[i].second;
      cli_options.base_namespace_specified = true;
    } else if (options[i].first == "internal_access") {
      cli_options.internal_access = true;
    } else {
      *error = "Unknown generator option: " + options[i].first;
      return false;
    }
  }

  string filename_error = "";
  std::string filename = GetOutputFile(file,
      cli_options.file_extension,
      cli_options.base_namespace_specified,
      cli_options.base_namespace,
      &filename_error);

  if (filename.empty()) {
    *error = filename_error;
    return false;
  }
  scoped_ptr<io::ZeroCopyOutputStream> output(
      generator_context->Open(filename));
  io::Printer printer(output.get(), '$');

  GenerateFile(file, &printer, &cli_options);

  return true;
}

}  // namespace csharp
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
