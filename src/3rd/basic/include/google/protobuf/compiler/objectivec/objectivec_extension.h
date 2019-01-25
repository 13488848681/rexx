
#ifndef GOOGLE_PROTOBUF_COMPILER_OBJECTIVEC_EXTENSION_H__
#define GOOGLE_PROTOBUF_COMPILER_OBJECTIVEC_EXTENSION_H__

#include <google/protobuf/stubs/common.h>

namespace google {
namespace protobuf {
class FieldDescriptor;  // descriptor.h
namespace io {
class Printer;  // printer.h
}
}

namespace protobuf {
namespace compiler {
namespace objectivec {

class ExtensionGenerator {
 public:
  ExtensionGenerator(const string& root_class_name,
                     const FieldDescriptor* descriptor);
  ~ExtensionGenerator();

  void GenerateMembersHeader(io::Printer* printer);
  void GenerateStaticVariablesInitialization(io::Printer* printer);
  void GenerateRegistrationSource(io::Printer* printer);

 private:
  string method_name_;
  string root_class_and_method_name_;
  const FieldDescriptor* descriptor_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ExtensionGenerator);
};
}  // namespace objectivec
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_OBJECTIVEC_MESSAGE_H__
