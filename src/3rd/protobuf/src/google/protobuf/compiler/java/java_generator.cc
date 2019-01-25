#include <google/protobuf/compiler/java/java_generator.h>

#include <memory>
#ifndef _SHARED_PTR_H
#include <google/protobuf/stubs/shared_ptr.h>
#endif

#include <google/protobuf/compiler/java/java_file.h>
#include <google/protobuf/compiler/java/java_generator_factory.h>
#include <google/protobuf/compiler/java/java_helpers.h>
#include <google/protobuf/compiler/java/java_options.h>
#include <google/protobuf/compiler/java/java_shared_code_generator.h>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/stubs/strutil.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace java {


JavaGenerator::JavaGenerator() {}
JavaGenerator::~JavaGenerator() {}

bool JavaGenerator::Generate(const FileDescriptor* file,
                             const string& parameter,
                             GeneratorContext* context,
                             string* error) const {
  // -----------------------------------------------------------------
  // parse generator options


  vector<pair<string, string> > options;
  ParseGeneratorParameter(parameter, &options);
  Options file_options;

  for (int i = 0; i < options.size(); i++) {
    if (options[i].first == "output_list_file") {
      file_options.output_list_file = options[i].second;
    } else if (options[i].first == "immutable") {
      file_options.generate_immutable_code = true;
    } else if (options[i].first == "mutable") {
      file_options.generate_mutable_code = true;
    } else if (options[i].first == "shared") {
      file_options.generate_shared_code = true;
    } else if (options[i].first == "annotate_code") {
      file_options.annotate_code = true;
    } else if (options[i].first == "annotation_list_file") {
      file_options.annotation_list_file = options[i].second;
    } else {
      *error = "Unknown generator option: " + options[i].first;
      return false;
    }
  }

  if (file_options.enforce_lite && file_options.generate_mutable_code) {
    *error = "lite runtime generator option cannot be used with mutable API.";
    return false;
  }

  // By default we generate immutable code and shared code for immutable API.
  if (!file_options.generate_immutable_code &&
      !file_options.generate_mutable_code &&
      !file_options.generate_shared_code) {
    file_options.generate_immutable_code = true;
    file_options.generate_shared_code = true;
  }

  // -----------------------------------------------------------------


  vector<string> all_files;
  vector<string> all_annotations;


  vector<FileGenerator*> file_generators;
  if (file_options.generate_immutable_code) {
    file_generators.push_back(new FileGenerator(file, file_options,
                                                /* immutable = */ true));
  }
  if (file_options.generate_mutable_code) {
    file_generators.push_back(new FileGenerator(file, file_options,
                                                /* mutable = */ false));
  }
  for (int i = 0; i < file_generators.size(); ++i) {
    if (!file_generators[i]->Validate(error)) {
      for (int j = 0; j < file_generators.size(); ++j) {
        delete file_generators[j];
      }
      return false;
    }
  }

  for (int i = 0; i < file_generators.size(); ++i) {
    FileGenerator* file_generator = file_generators[i];

    string package_dir = JavaPackageToDir(file_generator->java_package());

    string java_filename = package_dir;
    java_filename += file_generator->classname();
    java_filename += ".java";
    all_files.push_back(java_filename);
    string info_full_path = java_filename + ".pb.meta";
    if (file_options.annotate_code) {
      all_annotations.push_back(info_full_path);
    }

    // Generate main java file.
    google::protobuf::scoped_ptr<io::ZeroCopyOutputStream> output(
        context->Open(java_filename));
    GeneratedCodeInfo annotations;
    io::AnnotationProtoCollector<GeneratedCodeInfo> annotation_collector(
        &annotations);
    io::Printer printer(output.get(), '$', file_options.annotate_code
                                               ? &annotation_collector
                                               : NULL);

    file_generator->Generate(&printer);

    // Generate sibling files.
    file_generator->GenerateSiblings(package_dir, context, &all_files,
                                     &all_annotations);

    if (file_options.annotate_code) {
      google::protobuf::scoped_ptr<io::ZeroCopyOutputStream> info_output(
          context->Open(info_full_path));
      annotations.SerializeToZeroCopyStream(info_output.get());
    }
  }

  for (int i = 0; i < file_generators.size(); ++i) {
    delete file_generators[i];
  }
  file_generators.clear();

  // Generate output list if requested.
  if (!file_options.output_list_file.empty()) {
    // Generate output list.  This is just a simple text file placed in a
    // deterministic location which lists the .java files being generated.
    google::protobuf::scoped_ptr<io::ZeroCopyOutputStream> srclist_raw_output(
        context->Open(file_options.output_list_file));
    io::Printer srclist_printer(srclist_raw_output.get(), '$');
    for (int i = 0; i < all_files.size(); i++) {
      srclist_printer.Print("$filename$\n", "filename", all_files[i]);
    }
  }

  if (!file_options.annotation_list_file.empty()) {
    // Generate output list.  This is just a simple text file placed in a
    // deterministic location which lists the .java files being generated.
    google::protobuf::scoped_ptr<io::ZeroCopyOutputStream> annotation_list_raw_output(
        context->Open(file_options.annotation_list_file));
    io::Printer annotation_list_printer(annotation_list_raw_output.get(), '$');
    for (int i = 0; i < all_annotations.size(); i++) {
      annotation_list_printer.Print("$filename$\n", "filename",
                                    all_annotations[i]);
    }
  }

  return true;
}

}  // namespace java
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
