#ifndef GOOGLE_PROTOBUF_COMPILER_CSHARP_OPTIONS_H__
#define GOOGLE_PROTOBUF_COMPILER_CSHARP_OPTIONS_H__

#include <string>

#include <google/protobuf/stubs/common.h>
namespace google {
namespace protobuf {
namespace compiler {
namespace csharp {

// Generator options (used by csharp_generator.cc):
struct Options {
  Options() :
      file_extension(".cs"),
      base_namespace(""),
      base_namespace_specified(false),
      internal_access(false) {
  }
  // Extension of the generated file. Defaults to ".cs"
  string file_extension;
  // Base namespace to use to create directory hierarchy. Defaults to "".
  // This option allows the simple creation of a conventional C# file layout,
  // where directories are created relative to a project-specific base
  // namespace. For example, in a project with a base namespace of PetShop, a
  // proto of user.proto with a C# namespace of PetShop.Model.Shared would
  // generate Model/Shared/User.cs underneath the specified --csharp_out
  // directory.
  //
  // If no base namespace is specified, all files are generated in the
  // --csharp_out directory, with no subdirectories created automatically.
  string base_namespace;
  // Whether the base namespace has been explicitly specified by the user.
  // This is required as the base namespace can be explicitly set to the empty
  // string, meaning "create a full directory hierarchy, starting from the first
  // segment of the namespace."
  bool base_namespace_specified;
  // Whether the generated classes should have accessibility level of "internal".
  // Defaults to false that generates "public" classes.
  bool internal_access;
};

}  // namespace csharp
}  // namespace compiler
}  // namespace protobuf


}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_CSHARP_OPTIONS_H__
