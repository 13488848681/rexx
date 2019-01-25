
#ifndef GOOGLE_PROTOBUF_COMPILER_CSHARP_REFLECTION_CLASS_H__
#define GOOGLE_PROTOBUF_COMPILER_CSHARP_REFLECTION_CLASS_H__

#include <string>

#include <google/protobuf/compiler/code_generator.h>
#include <google/protobuf/compiler/csharp/csharp_source_generator_base.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace csharp {

class ReflectionClassGenerator : public SourceGeneratorBase {
 public:
  ReflectionClassGenerator(const FileDescriptor* file, const Options* options);
  ~ReflectionClassGenerator();

  void Generate(io::Printer* printer);

 private:
  const FileDescriptor* file_;

  std::string namespace_;
  std::string reflectionClassname_;

  void WriteIntroduction(io::Printer* printer);
  void WriteDescriptor(io::Printer* printer);
  void WriteGeneratedCodeInfo(const Descriptor* descriptor,
                              io::Printer* printer,
                              bool last);

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ReflectionClassGenerator);
};

}  // namespace csharp
}  // namespace compiler
}  // namespace protobuf
}  // namespace google

#endif  // GOOGLE_PROTOBUF_COMPILER_CSHARP_REFLECTION_CLASS_H__
