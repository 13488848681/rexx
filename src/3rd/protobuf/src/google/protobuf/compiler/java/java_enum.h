#ifndef GOOGLE_PROTOBUF_COMPILER_JAVA_ENUM_H__
#define GOOGLE_PROTOBUF_COMPILER_JAVA_ENUM_H__

#include <string>
#include <vector>
#include <google/protobuf/descriptor.h>

namespace google {
namespace protobuf {
  namespace compiler {
    namespace java {
      class Context;           // context.h
      class ClassNameResolver; // name_resolver.h
    }
  }
  namespace io {
    class Printer;             // printer.h
  }
}

namespace protobuf {
namespace compiler {
namespace java {

class EnumGenerator {
 public:
  EnumGenerator(const EnumDescriptor* descriptor, bool immutable_api,
                Context* context);
  ~EnumGenerator();

  void Generate(io::Printer* printer);

 private:
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

  bool immutable_api_;

  Context* context_;
  ClassNameResolver* name_resolver_;

  bool CanUseEnumValues();

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(EnumGenerator);
};

}  // namespace java
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_JAVA_ENUM_H__
