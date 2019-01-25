
#ifndef GOOGLE_PROTOBUF_COMPILER_CSHARP_DOC_COMMENT_H__
#define GOOGLE_PROTOBUF_COMPILER_CSHARP_DOC_COMMENT_H__

#include <google/protobuf/io/printer.h>
#include <google/protobuf/descriptor.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace csharp {
    void WriteMessageDocComment(io::Printer* printer, const Descriptor* message);
    void WritePropertyDocComment(io::Printer* printer, const FieldDescriptor* field);
    void WriteEnumDocComment(io::Printer* printer, const EnumDescriptor* enumDescriptor);
    void WriteEnumValueDocComment(io::Printer* printer, const EnumValueDescriptor* value);
    void WriteMethodDocComment(io::Printer* printer, const MethodDescriptor* method);
}  // namespace csharp
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_CSHARP_DOC_COMMENT_H__
