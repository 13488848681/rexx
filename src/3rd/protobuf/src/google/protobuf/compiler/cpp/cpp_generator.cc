#include <google/protobuf/compiler/cpp/cpp_generator.h>

#include <vector>
#include <memory>
#ifndef _SHARED_PTR_H
#include <google/protobuf/stubs/shared_ptr.h>
#endif
#include <utility>

#include <google/protobuf/compiler/cpp/cpp_file.h>
#include <google/protobuf/compiler/cpp/cpp_helpers.h>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/descriptor.pb.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace cpp {

CppGenerator::CppGenerator() {}
CppGenerator::~CppGenerator() {}

bool CppGenerator::Generate(const FileDescriptor* file,
                            const string& parameter,
                            GeneratorContext* generator_context,
                            string* error) const {
  vector<pair<string, string> > options;
  ParseGeneratorParameter(parameter, &options);

  // -----------------------------------------------------------------
  // parse generator options

  // TODO(kenton):  If we ever have more options, we may want to create a
  //   class that encapsulates them which we can pass down to all the
  //   generator classes.  Currently we pass dllexport_decl down to all of
  //   them via the constructors, but we don't want to have to add another
  //   constructor parameter for every option.

  // If the dllexport_decl option is passed to the compiler, we need to write
  // it in front of every symbol that should be exported if this .proto is
  // compiled into a Windows DLL.  E.g., if the user invokes the protocol
  // compiler as:
  //   protoc --cpp_out=dllexport_decl=FOO_EXPORT:outdir foo.proto
  // then we'll define classes like this:
  //   class FOO_EXPORT Foo {
  //     ...
  //   }
  // FOO_EXPORT is a macro which should expand to __declspec(dllexport) or
  // __declspec(dllimport) depending on what is being compiled.
  //
  Options file_options;

  for (int i = 0; i < options.size(); i++) {
    if (options[i].first == "dllexport_decl") {
      file_options.dllexport_decl = options[i].second;
    } else if (options[i].first == "safe_boundary_check") {
      file_options.safe_boundary_check = true;
    } else if (options[i].first == "annotate_headers") {
      file_options.annotate_headers = true;
    } else if (options[i].first == "annotation_pragma_name") {
      file_options.annotation_pragma_name = options[i].second;
    } else if (options[i].first == "annotation_guard_name") {
      file_options.annotation_guard_name = options[i].second;
    } else if (options[i].first == "lite") {
      file_options.enforce_lite = true;
    } else {
      *error = "Unknown generator option: " + options[i].first;
      return false;
    }
  }

  // -----------------------------------------------------------------


  string basename = StripProto(file->name());

  FileGenerator file_generator(file, file_options);

  // Generate header(s).
  if (file_options.proto_h) {
    google::protobuf::scoped_ptr<io::ZeroCopyOutputStream> output(
        generator_context->Open(basename + ".proto.h"));
    GeneratedCodeInfo annotations;
    io::AnnotationProtoCollector<GeneratedCodeInfo> annotation_collector(
        &annotations);
    string info_path = basename + ".proto.h.meta";
    io::Printer printer(output.get(), '$', file_options.annotate_headers
                                               ? &annotation_collector
                                               : NULL);
    file_generator.GenerateProtoHeader(
        &printer, file_options.annotate_headers ? info_path : "");
    if (file_options.annotate_headers) {
      google::protobuf::scoped_ptr<io::ZeroCopyOutputStream> info_output(
          generator_context->Open(info_path));
      annotations.SerializeToZeroCopyStream(info_output.get());
    }
  }

  basename.append(".pb");
  {
    google::protobuf::scoped_ptr<io::ZeroCopyOutputStream> output(
        generator_context->Open(basename + ".h"));
    GeneratedCodeInfo annotations;
    io::AnnotationProtoCollector<GeneratedCodeInfo> annotation_collector(
        &annotations);
    string info_path = basename + ".h.meta";
    io::Printer printer(output.get(), '$', file_options.annotate_headers
                                               ? &annotation_collector
                                               : NULL);
    file_generator.GeneratePBHeader(
        &printer, file_options.annotate_headers ? info_path : "");
    if (file_options.annotate_headers) {
      google::protobuf::scoped_ptr<io::ZeroCopyOutputStream> info_output(
          generator_context->Open(info_path));
      annotations.SerializeToZeroCopyStream(info_output.get());
    }
  }

  // Generate cc file.
  {
    google::protobuf::scoped_ptr<io::ZeroCopyOutputStream> output(
        generator_context->Open(basename + ".cc"));
    io::Printer printer(output.get(), '$');
    file_generator.GenerateSource(&printer);
  }

  return true;
}

}  // namespace cpp
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
