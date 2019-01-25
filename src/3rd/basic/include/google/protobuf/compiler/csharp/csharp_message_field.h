
#ifndef GOOGLE_PROTOBUF_COMPILER_CSHARP_MESSAGE_FIELD_H__
#define GOOGLE_PROTOBUF_COMPILER_CSHARP_MESSAGE_FIELD_H__

#include <string>

#include <google/protobuf/compiler/code_generator.h>
#include <google/protobuf/compiler/csharp/csharp_field_base.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace csharp {

class MessageFieldGenerator : public FieldGeneratorBase {
 public:
  MessageFieldGenerator(const FieldDescriptor* descriptor,
                        int fieldOrdinal,
                        const Options *options);
  ~MessageFieldGenerator();

  virtual void GenerateCodecCode(io::Printer* printer);
  virtual void GenerateCloningCode(io::Printer* printer);
  virtual void GenerateFreezingCode(io::Printer* printer);
  virtual void GenerateMembers(io::Printer* printer);
  virtual void GenerateMergingCode(io::Printer* printer);
  virtual void GenerateParsingCode(io::Printer* printer);
  virtual void GenerateSerializationCode(io::Printer* printer);
  virtual void GenerateSerializedSizeCode(io::Printer* printer);

  virtual void WriteHash(io::Printer* printer);
  virtual void WriteEquals(io::Printer* printer);
  virtual void WriteToString(io::Printer* printer);

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(MessageFieldGenerator);
};

class MessageOneofFieldGenerator : public MessageFieldGenerator {
 public:
  MessageOneofFieldGenerator(const FieldDescriptor* descriptor,
                             int fieldOrdinal,
                             const Options *options);
  ~MessageOneofFieldGenerator();

  virtual void GenerateCloningCode(io::Printer* printer);
  virtual void GenerateMembers(io::Printer* printer);
  virtual void WriteToString(io::Printer* printer);
  virtual void GenerateParsingCode(io::Printer* printer);

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(MessageOneofFieldGenerator);
};

}  // namespace csharp
}  // namespace compiler
}  // namespace protobuf
}  // namespace google

#endif  // GOOGLE_PROTOBUF_COMPILER_CSHARP_MESSAGE_FIELD_H__

