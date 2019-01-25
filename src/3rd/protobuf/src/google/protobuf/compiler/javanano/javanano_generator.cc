
#include <google/protobuf/compiler/javanano/javanano_params.h>
#include <google/protobuf/compiler/javanano/javanano_generator.h>
#include <google/protobuf/compiler/javanano/javanano_file.h>
#include <google/protobuf/compiler/javanano/javanano_helpers.h>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/stubs/strutil.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace javanano {

namespace {

string TrimString(const string& s) {
  string::size_type start = s.find_first_not_of(" \n\r\t");
  if (start == string::npos) {
    return "";
  }
  string::size_type end = s.find_last_not_of(" \n\r\t") + 1;
  return s.substr(start, end - start);
}

} // namespace

void UpdateParamsRecursively(Params& params,
    const FileDescriptor* file) {
  // Add any parameters for this file
  if (file->options().has_java_outer_classname()) {
    params.set_java_outer_classname(
      file->name(), file->options().java_outer_classname());
  }
  if (file->options().has_java_package()) {
    string result = file->options().java_package();
    if (!result.empty()) {
      result += ".";
    }
    result += "nano";
    params.set_java_package(
      file->name(), result);
  }
  if (file->options().has_java_multiple_files()) {
    params.set_java_multiple_files(
      file->name(), file->options().java_multiple_files());
  }

  // Loop through all dependent files recursively
  // adding dep
  for (int i = 0; i < file->dependency_count(); i++) {
    UpdateParamsRecursively(params, file->dependency(i));
  }
}

JavaNanoGenerator::JavaNanoGenerator() {}
JavaNanoGenerator::~JavaNanoGenerator() {}

bool JavaNanoGenerator::Generate(const FileDescriptor* file,
                             const string& parameter,
                             GeneratorContext* output_directory,
                             string* error) const {
  vector<pair<string, string> > options;

  ParseGeneratorParameter(parameter, &options);

  // -----------------------------------------------------------------
  // parse generator options

  // Name a file where we will write a list of generated file names, one
  // per line.
  string output_list_file;
  Params params(file->name());

  // Update per file params
  UpdateParamsRecursively(params, file);

  // Replace any existing options with ones from command line
  for (int i = 0; i < options.size(); i++) {
    string option_name = TrimString(options[i].first);
    string option_value = TrimString(options[i].second);
    if (option_name == "output_list_file") {
      output_list_file = option_value;
    } else if (option_name == "java_package") {
        vector<string> parts;
        SplitStringUsing(option_value, "|", &parts);
        if (parts.size() != 2) {
          *error = "Bad java_package, expecting filename|PackageName found '"
            + option_value + "'";
          return false;
        }
        params.set_java_package(parts[0], parts[1]);
    } else if (option_name == "java_outer_classname") {
        vector<string> parts;
        SplitStringUsing(option_value, "|", &parts);
        if (parts.size() != 2) {
          *error = "Bad java_outer_classname, "
                   "expecting filename|ClassName found '"
                   + option_value + "'";
          return false;
        }
        params.set_java_outer_classname(parts[0], parts[1]);
    } else if (option_name == "store_unknown_fields") {
      params.set_store_unknown_fields(option_value == "true");
    } else if (option_name == "java_multiple_files") {
      params.set_override_java_multiple_files(option_value == "true");
    } else if (option_name == "java_nano_generate_has") {
      params.set_generate_has(option_value == "true");
    } else if (option_name == "enum_style") {
      params.set_java_enum_style(option_value == "java");
    } else if (option_name == "optional_field_style") {
      params.set_optional_field_accessors(option_value == "accessors");
      params.set_use_reference_types_for_primitives(option_value == "reftypes"
          || option_value == "reftypes_compat_mode");
      params.set_reftypes_primitive_enums(
          option_value == "reftypes_compat_mode");
      if (option_value == "reftypes_compat_mode") {
        params.set_generate_clear(false);
      }
    } else if (option_name == "generate_equals") {
      params.set_generate_equals(option_value == "true");
    } else if (option_name == "ignore_services") {
      params.set_ignore_services(option_value == "true");
    } else if (option_name == "parcelable_messages") {
      params.set_parcelable_messages(option_value == "true");
    } else if (option_name == "generate_clone") {
      params.set_generate_clone(option_value == "true");
    } else if (option_name == "generate_intdefs") {
      params.set_generate_intdefs(option_value == "true");
    } else if (option_name == "generate_clear") {
      params.set_generate_clear(option_value == "true");
    } else {
      *error = "Ignore unknown javanano generator option: " + option_name;
    }
  }

  // Check illegal parameter combinations
  // Note: the enum-like optional_field_style generator param ensures
  // that we can never have illegal combinations of field styles
  // (e.g. reftypes and accessors can't be on at the same time).
  if (params.generate_has()
      && (params.optional_field_accessors()
          || params.use_reference_types_for_primitives())) {
    error->assign("java_nano_generate_has=true cannot be used in conjunction"
        " with optional_field_style=accessors or optional_field_style=reftypes");
    return false;
  }

  // -----------------------------------------------------------------

  FileGenerator file_generator(file, params);
  if (!file_generator.Validate(error)) {
    return false;
  }

  string package_dir =
    StringReplace(file_generator.java_package(), ".", "/", true);
  if (!package_dir.empty()) package_dir += "/";

  vector<string> all_files;

  if (IsOuterClassNeeded(params, file)) {
    string java_filename = package_dir;
    java_filename += file_generator.classname();
    java_filename += ".java";
    all_files.push_back(java_filename);

    // Generate main java file.
    scoped_ptr<io::ZeroCopyOutputStream> output(
      output_directory->Open(java_filename));
    io::Printer printer(output.get(), '$');
    file_generator.Generate(&printer);
  }

  // Generate sibling files.
  file_generator.GenerateSiblings(package_dir, output_directory, &all_files);

  // Generate output list if requested.
  if (!output_list_file.empty()) {
    // Generate output list.  This is just a simple text file placed in a
    // deterministic location which lists the .java files being generated.
    scoped_ptr<io::ZeroCopyOutputStream> srclist_raw_output(
      output_directory->Open(output_list_file));
    io::Printer srclist_printer(srclist_raw_output.get(), '$');
    for (int i = 0; i < all_files.size(); i++) {
      srclist_printer.Print("$filename$\n", "filename", all_files[i]);
    }
  }

  return true;
}

}  // namespace java
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
