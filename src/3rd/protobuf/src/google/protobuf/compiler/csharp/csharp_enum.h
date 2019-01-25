#ifndef GOOGLE_PROTOBUF_COMPILER_CSHARP_ENUM_H__
#define GOOGLE_PROTOBUF_COMPILER_CSHARP_ENUM_H__

#include <string>

#include <google/protobuf/compiler/code_generator.h>
#include <google/protobuf/compiler/csharp/csharp_source_generator_base.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace csharp {

class EnumGenerator : public SourceGeneratorBase {
 public:
  EnumGenerator(const EnumDescriptor* descriptor, const Options* options);
  ~EnumGenerator();

  void Generate(io::Printer* printer);

 private:
  const EnumDescriptor* descriptor_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(EnumGenerator);
};

}  // namespace csharp
}  // namespace compiler
}  // namespace protobuf
}  // namespace google

#endif  // GOOGLE_PROTOBUF_COMPILER_CSHARP_ENUM_H__

