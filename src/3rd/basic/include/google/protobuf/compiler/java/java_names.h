
#ifndef GOOGLE_PROTOBUF_COMPILER_JAVA_NAMES_H__
#define GOOGLE_PROTOBUF_COMPILER_JAVA_NAMES_H__

#include <string>

namespace google {
namespace protobuf {

class Descriptor;
class EnumDescriptor;
class FileDescriptor;
class ServiceDescriptor;

namespace compiler {
namespace java {

// Requires:
//   descriptor != NULL
//
// Returns:
//   The fully-qualified Java class name.
string ClassName(const Descriptor* descriptor);

// Requires:
//   descriptor != NULL
//
// Returns:
//   The fully-qualified Java class name.
string ClassName(const EnumDescriptor* descriptor);

// Requires:
//   descriptor != NULL
//
// Returns:
//   The fully-qualified Java class name.
string ClassName(const FileDescriptor* descriptor);

// Requires:
//   descriptor != NULL
//
// Returns:
//   The fully-qualified Java class name.
string ClassName(const ServiceDescriptor* descriptor);

}  // namespace java
}  // namespace compiler
}  // namespace protobuf
}  // namespace google

#endif  // GOOGLE_PROTOBUF_COMPILER_JAVA_NAMES_H__
