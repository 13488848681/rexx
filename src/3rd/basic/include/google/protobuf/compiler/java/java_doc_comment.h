
#ifndef GOOGLE_PROTOBUF_COMPILER_JAVA_DOC_COMMENT_H__
#define GOOGLE_PROTOBUF_COMPILER_JAVA_DOC_COMMENT_H__

#include <google/protobuf/descriptor.h>

namespace google {
namespace protobuf {
  namespace io {
    class Printer;             // printer.h
  }
}

namespace protobuf {
namespace compiler {
namespace java {

void WriteMessageDocComment(io::Printer* printer, const Descriptor* message);
void WriteFieldDocComment(io::Printer* printer, const FieldDescriptor* field);
void WriteEnumDocComment(io::Printer* printer, const EnumDescriptor* enum_);
void WriteEnumValueDocComment(io::Printer* printer,
                              const EnumValueDescriptor* value);
void WriteServiceDocComment(io::Printer* printer,
                            const ServiceDescriptor* service);
void WriteMethodDocComment(io::Printer* printer,
                           const MethodDescriptor* method);

// Exposed for testing only.
LIBPROTOC_EXPORT string EscapeJavadoc(const string& input);

}  // namespace java
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_JAVA_DOC_COMMENT_H__
