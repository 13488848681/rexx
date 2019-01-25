
#ifndef GOOGLE_PROTOBUF_COMPILER_OBJECTIVEC_ENUM_H__
#define GOOGLE_PROTOBUF_COMPILER_OBJECTIVEC_ENUM_H__

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

class EnumGenerator {
 public:
  explicit EnumGenerator(const EnumDescriptor* descriptor);
  ~EnumGenerator();

  void GenerateHeader(io::Printer* printer);
  void GenerateSource(io::Printer* printer);

  const string& name() const { return name_; }

 private:
  const EnumDescriptor* descriptor_;
  vector<const EnumValueDescriptor*> base_values_;
  vector<const EnumValueDescriptor*> all_values_;
  const string name_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(EnumGenerator);
};

}  // namespace objectivec
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_OBJECTIVEC_ENUM_H__
