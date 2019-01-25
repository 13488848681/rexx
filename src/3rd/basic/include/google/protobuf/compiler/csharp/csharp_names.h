
#ifndef GOOGLE_PROTOBUF_COMPILER_CSHARP_NAMES_H__
#define GOOGLE_PROTOBUF_COMPILER_CSHARP_NAMES_H__

#include <string>

namespace google {
namespace protobuf {

class Descriptor;
class EnumDescriptor;
class FileDescriptor;
class ServiceDescriptor;

namespace compiler {
namespace csharp {

// Requires:
//   descriptor != NULL
//
// Returns:
//   The namespace to use for given file descriptor.
string GetFileNamespace(const FileDescriptor* descriptor);

// Requires:
//   descriptor != NULL
//
// Returns:
//   The fully-qualified C# class name.
string GetClassName(const Descriptor* descriptor);

// Requires:
//   descriptor != NULL
//
// Returns:
//   The fully-qualified name of the C# class that provides
//   access to the file descriptor. Proto compiler generates
//   such class for each .proto file processed.
string GetReflectionClassName(const FileDescriptor* descriptor);

// Generates output file name for given file descriptor. If generate_directories
// is true, the output file will be put under directory corresponding to file's
// namespace. base_namespace can be used to strip some of the top level
// directories. E.g. for file with namespace "Bar.Foo" and base_namespace="Bar",
// the resulting file will be put under directory "Foo" (and not "Bar/Foo").
//
// Requires:
//   descriptor != NULL
//   error != NULL
//
//  Returns:
//    The file name to use as output file for given file descriptor. In case
//    of failure, this function will return empty string and error parameter
//    will contain the error message.
string GetOutputFile(
    const google::protobuf::FileDescriptor* descriptor,
    const string file_extension,
    const bool generate_directories,
    const string base_namespace,
    string* error);

}  // namespace csharp
}  // namespace compiler
}  // namespace protobuf
}  // namespace google

#endif  // GOOGLE_PROTOBUF_COMPILER_CSHARP_NAMES_H__
