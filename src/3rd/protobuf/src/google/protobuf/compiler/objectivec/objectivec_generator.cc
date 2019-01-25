
#include <iostream>
#include <google/protobuf/compiler/objectivec/objectivec_generator.h>
#include <google/protobuf/compiler/objectivec/objectivec_file.h>
#include <google/protobuf/compiler/objectivec/objectivec_helpers.h>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/stubs/strutil.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace objectivec {

ObjectiveCGenerator::ObjectiveCGenerator() {}

ObjectiveCGenerator::~ObjectiveCGenerator() {}

bool ObjectiveCGenerator::Generate(const FileDescriptor* file,
                                   const string& parameter,
                                   OutputDirectory* output_directory,
                                   string* error) const {
  // -----------------------------------------------------------------
  // Parse generator options. These options are passed to the compiler using the
  // --objc_opt flag. The options are passed as a comma separated list of
  // options along with their values. If the option appears multiple times, only
  // the last value will be considered.
  //
  // e.g. protoc ... --objc_opt=expected_prefixes=file.txt,generate_for_named_framework=MyFramework

  Options generation_options;

  vector<pair<string, string> > options;
  ParseGeneratorParameter(parameter, &options);
  for (int i = 0; i < options.size(); i++) {
    if (options[i].first == "expected_prefixes_path") {
      // Path to find a file containing the expected prefixes
      // (objc_class_prefix "PREFIX") for proto packages (package NAME). The
      // generator will then issue warnings/errors if in the proto files being
      // generated the option is not listed/wrong/etc in the file.
      //
      // The format of the file is:
      //   - An entry is a line of "package=prefix".
      //   - Comments start with "#".
      //   - A comment can go on a line after a expected package/prefix pair.
      //     (i.e. - "package=prefix # comment")
      //
      // There is no validation that the prefixes are good prefixes, it is
      // assumed that they are when you create the file.
      generation_options.expected_prefixes_path = options[i].second;
    } else if (options[i].first == "generate_for_named_framework") {
      // The name of the framework that protos are being generated for. This
      // will cause the #import statements to be framework based using this
      // name (i.e. - "#import <NAME/proto.pbobjc.h>).
      //
      // NOTE: If this option is used with
      // named_framework_to_proto_path_mappings_path, then this is effectively
      // the "default" framework name used for everything that wasn't mapped by
      // the mapping file.
      generation_options.generate_for_named_framework = options[i].second;
    } else if (options[i].first == "named_framework_to_proto_path_mappings_path") {
      // Path to find a file containing the list of framework names and proto
      // files. The generator uses this to decide if a proto file
      // referenced should use a framework style import vs. a user level import
      // (#import <FRAMEWORK/file.pbobjc.h> vs #import "dir/file.pbobjc.h").
      //
      // The format of the file is:
      //   - An entry is a line of "frameworkName: file.proto, dir/file2.proto".
      //   - Comments start with "#".
      //   - A comment can go on a line after a expected package/prefix pair.
      //     (i.e. - "frameworkName: file.proto # comment")
      //
      // Any number of files can be listed for a framework, just separate them
      // with commas.
      //
      // There can be multiple lines listing the same frameworkName incase it
      // has a lot of proto files included in it; having multiple lines makes
      // things easier to read. If a proto file is not configured in the
      // mappings file, it will use the default framework name if one was passed
      // with generate_for_named_framework, or the relative path to it's include
      // path otherwise.
      generation_options.named_framework_to_proto_path_mappings_path = options[i].second;
    } else {
      *error = "error: Unknown generator option: " + options[i].first;
      return false;
    }
  }

  // -----------------------------------------------------------------

  // Validate the objc prefix/package pairing.
  if (!ValidateObjCClassPrefix(file, generation_options, error)) {
    // *error will have been filled in.
    return false;
  }

  FileGenerator file_generator(file, generation_options);
  string filepath = FilePath(file);

  // Generate header.
  {
    scoped_ptr<io::ZeroCopyOutputStream> output(
        output_directory->Open(filepath + ".pbobjc.h"));
    io::Printer printer(output.get(), '$');
    file_generator.GenerateHeader(&printer);
  }

  // Generate m file.
  {
    scoped_ptr<io::ZeroCopyOutputStream> output(
        output_directory->Open(filepath + ".pbobjc.m"));
    io::Printer printer(output.get(), '$');
    file_generator.GenerateSource(&printer);
  }

  return true;
}

}  // namespace objectivec
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
