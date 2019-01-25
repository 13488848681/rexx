
#ifndef GOOGLE_PROTOBUF_COMPILER_JAVANANO_ENUM_H__
#define GOOGLE_PROTOBUF_COMPILER_JAVANANO_ENUM_H__

#include <string>
#include <vector>

#include <google/protobuf/compiler/javanano/javanano_params.h>
#include <google/protobuf/descriptor.h>

namespace google {
namespace protobuf {
  namespace io {
    class Printer;             // printer.h
  }
}

namespace protobuf {
namespace compiler {
namespace javanano {

class EnumGenerator {
 public:
  explicit EnumGenerator(const EnumDescriptor* descriptor, const Params& params);
  ~EnumGenerator();

  void Generate(io::Printer* printer);

 private:
  const Params& params_;
  const EnumDescriptor* descriptor_;

  // The proto language allows multiple enum constants to have the same numeric
  // value.  Java, however, does not allow multiple enum constants to be
  // considered equivalent.  We treat the first defined constant for any
  // given numeric value as "canonical" and the rest as aliases of that
  // canonical value.
  vector<const EnumValueDescriptor*> canonical_values_;

  struct Alias {
    const EnumValueDescriptor* value;
    const EnumValueDescriptor* canonical_value;
  };
  vector<Alias> aliases_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(EnumGenerator);
};

}  // namespace javanano
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_JAVANANO_ENUM_H__
