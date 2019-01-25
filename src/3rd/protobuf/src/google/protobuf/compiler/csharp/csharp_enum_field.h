#ifndef GOOGLE_PROTOBUF_COMPILER_CSHARP_ENUM_FIELD_H__
#define GOOGLE_PROTOBUF_COMPILER_CSHARP_ENUM_FIELD_H__

#include <string>

#include <google/protobuf/compiler/code_generator.h>
#include <google/protobuf/compiler/csharp/csharp_primitive_field.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace csharp {

class EnumFieldGenerator : public PrimitiveFieldGenerator {
 public:
  EnumFieldGenerator(const FieldDescriptor* descriptor,
                     int fieldOrdinal,
                     const Options *options);
  ~EnumFieldGenerator();

  virtual void GenerateCodecCode(io::Printer* printer);
  virtual void GenerateParsingCode(io::Printer* printer);
  virtual void GenerateSerializationCode(io::Printer* printer);
  virtual void GenerateSerializedSizeCode(io::Printer* printer);

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(EnumFieldGenerator);
};

class EnumOneofFieldGenerator : public PrimitiveOneofFieldGenerator {
 public:
  EnumOneofFieldGenerator(const FieldDescriptor* descriptor,
                          int fieldOrdinal,
                          const Options *options);
  ~EnumOneofFieldGenerator();

  virtual void GenerateParsingCode(io::Printer* printer);
  virtual void GenerateSerializationCode(io::Printer* printer);
  virtual void GenerateSerializedSizeCode(io::Printer* printer);

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(EnumOneofFieldGenerator);
};

}  // namespace csharp
}  // namespace compiler
}  // namespace protobuf
}  // namespace google

#endif  // GOOGLE_PROTOBUF_COMPILER_CSHARP_ENUM_FIELD_H__

