
#ifndef GOOGLE_PROTOBUF_COMPILER_CSHARP_HELPERS_H__
#define GOOGLE_PROTOBUF_COMPILER_CSHARP_HELPERS_H__

#include <string>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/compiler/code_generator.h>
#include <google/protobuf/io/printer.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace csharp {

struct Options;
class FieldGeneratorBase;

// TODO: start using this enum.
enum CSharpType {
  CSHARPTYPE_INT32 = 1,
  CSHARPTYPE_INT64 = 2,
  CSHARPTYPE_UINT32 = 3,
  CSHARPTYPE_UINT64 = 4,
  CSHARPTYPE_FLOAT = 5,
  CSHARPTYPE_DOUBLE = 6,
  CSHARPTYPE_BOOL = 7,
  CSHARPTYPE_STRING = 8,
  CSHARPTYPE_BYTESTRING = 9,
  CSHARPTYPE_MESSAGE = 10,
  CSHARPTYPE_ENUM = 11,
  MAX_CSHARPTYPE = 11
};

// Converts field type to corresponding C# type.
CSharpType GetCSharpType(FieldDescriptor::Type type);

std::string StripDotProto(const std::string& proto_file);

// Gets unqualified name of the reflection class
std::string GetReflectionClassUnqualifiedName(const FileDescriptor* descriptor);

std::string GetClassName(const EnumDescriptor* descriptor);

std::string GetFieldName(const FieldDescriptor* descriptor);

std::string GetFieldConstantName(const FieldDescriptor* field);

std::string GetPropertyName(const FieldDescriptor* descriptor);

int GetFixedSize(FieldDescriptor::Type type);

std::string UnderscoresToCamelCase(const std::string& input,
                                   bool cap_next_letter,
                                   bool preserve_period);

inline std::string UnderscoresToCamelCase(const std::string& input, bool cap_next_letter) {
  return UnderscoresToCamelCase(input, cap_next_letter, false);
}

std::string UnderscoresToPascalCase(const std::string& input);

// Note that we wouldn't normally want to export this (we're not expecting
// it to be used outside libprotoc itself) but this exposes it for testing.
std::string LIBPROTOBUF_EXPORT GetEnumValueName(const std::string& enum_name, const std::string& enum_value_name);

// TODO(jtattermusch): perhaps we could move this to strutil
std::string StringToBase64(const std::string& input);

std::string FileDescriptorToBase64(const FileDescriptor* descriptor);

FieldGeneratorBase* CreateFieldGenerator(const FieldDescriptor* descriptor,
                                         int fieldOrdinal,
                                         const Options* options);

// Determines whether the given message is a map entry message,
// i.e. one implicitly created by protoc due to a map<key, value> field.
inline bool IsMapEntryMessage(const Descriptor* descriptor) {
  return descriptor->options().map_entry();
}

// Determines whether we're generating code for the proto representation of
// descriptors etc, for use in the runtime. This is the only type which is
// allowed to use proto2 syntax, and it generates internal classes.
inline bool IsDescriptorProto(const FileDescriptor* descriptor) {
  return descriptor->name() == "google/protobuf/descriptor.proto";
}

inline bool IsWrapperType(const FieldDescriptor* descriptor) {
  return descriptor->type() == FieldDescriptor::TYPE_MESSAGE &&
      descriptor->message_type()->file()->name() == "google/protobuf/wrappers.proto";
}

}  // namespace csharp
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_CSHARP_HELPERS_H__
