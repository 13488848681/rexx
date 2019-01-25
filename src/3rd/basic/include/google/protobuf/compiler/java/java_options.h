
#ifndef GOOGLE_PROTOBUF_COMPILER_JAVA_OPTIONS_H__
#define GOOGLE_PROTOBUF_COMPILER_JAVA_OPTIONS_H__

#include <string>

namespace google {
namespace protobuf {
namespace compiler {
namespace java {

// Generator options
struct Options {
  Options()
      : generate_immutable_code(false),
        generate_mutable_code(false),
        generate_shared_code(false),
        enforce_lite(false),
        annotate_code(false) {
  }

  bool generate_immutable_code;
  bool generate_mutable_code;
  bool generate_shared_code;
  // When set, the protoc will generate the current files and all the transitive
  // dependencies as lite runtime.
  bool enforce_lite;
  // If true, we should build .meta files and emit @Generated annotations into
  // generated code.
  bool annotate_code;
  // Name of a file where we will write a list of generated .meta file names,
  // one per line.
  string annotation_list_file;
  // Name of a file where we will write a list of generated file names, one
  // per line.
  string output_list_file;
};

}  // namespace java
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_JAVA_OPTIONS_H__
