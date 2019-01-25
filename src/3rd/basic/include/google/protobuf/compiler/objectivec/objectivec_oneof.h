
#ifndef GOOGLE_PROTOBUF_COMPILER_OBJECTIVEC_ONEOF_H__
#define GOOGLE_PROTOBUF_COMPILER_OBJECTIVEC_ONEOF_H__

#include <string>
#include <set>
#include <vector>
#include <google/protobuf/descriptor.h>

namespace google {
namespace protobuf {
namespace io {
class Printer;  // printer.h
}
}

namespace protobuf {
namespace compiler {
namespace objectivec {

class OneofGenerator {
 public:
  explicit OneofGenerator(const OneofDescriptor* descriptor);
  ~OneofGenerator();

  void SetOneofIndexBase(int index_base);

  void GenerateCaseEnum(io::Printer* printer);

  void GeneratePublicCasePropertyDeclaration(io::Printer* printer);
  void GenerateClearFunctionDeclaration(io::Printer* printer);

  void GeneratePropertyImplementation(io::Printer* printer);
  void GenerateClearFunctionImplementation(io::Printer* printer);

  string DescriptorName(void) const;
  string HasIndexAsString(void) const;

 private:
  const OneofDescriptor* descriptor_;
  map<string, string> variables_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(OneofGenerator);
};

}  // namespace objectivec
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_OBJECTIVEC_ONEOF_H__
