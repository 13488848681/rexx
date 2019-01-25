
#ifndef GOOGLE_PROTOBUF_COMPILER_JAVANANO_EXTENSION_H_
#define GOOGLE_PROTOBUF_COMPILER_JAVANANO_EXTENSION_H_

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/compiler/javanano/javanano_params.h>
#include <google/protobuf/descriptor.pb.h>


namespace google {
namespace protobuf {
  namespace io {
    class Printer;             // printer.h
  }
}

namespace protobuf {
namespace compiler {
namespace javanano {

class ExtensionGenerator {
 public:
  explicit ExtensionGenerator(const FieldDescriptor* descriptor, const Params& params);
  ~ExtensionGenerator();

  void Generate(io::Printer* printer) const;

 private:
  const Params& params_;
  const FieldDescriptor* descriptor_;
  map<string, string> variables_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ExtensionGenerator);
};

}  // namespace javanano
}  // namespace compiler
}  // namespace protobuf
}  // namespace google

#endif  // GOOGLE_PROTOBUF_COMPILER_JAVANANO_EXTENSION_H_
