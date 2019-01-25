
#ifndef GOOGLE_PROTOBUF_COMPILER_JAVANANO_MESSAGE_FIELD_H__
#define GOOGLE_PROTOBUF_COMPILER_JAVANANO_MESSAGE_FIELD_H__

#include <map>
#include <string>
#include <google/protobuf/compiler/javanano/javanano_field.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace javanano {

class MessageFieldGenerator : public FieldGenerator {
 public:
  explicit MessageFieldGenerator(
      const FieldDescriptor* descriptor, const Params& params);
  ~MessageFieldGenerator();

  // implements FieldGenerator ---------------------------------------
  void GenerateMembers(io::Printer* printer, bool lazy_init) const;
  void GenerateClearCode(io::Printer* printer) const;
  void GenerateMergingCode(io::Printer* printer) const;
  void GenerateSerializationCode(io::Printer* printer) const;
  void GenerateSerializedSizeCode(io::Printer* printer) const;
  void GenerateEqualsCode(io::Printer* printer) const;
  void GenerateHashCodeCode(io::Printer* printer) const;
  void GenerateFixClonedCode(io::Printer* printer) const;

 private:
  const FieldDescriptor* descriptor_;
  map<string, string> variables_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(MessageFieldGenerator);
};

class MessageOneofFieldGenerator : public FieldGenerator {
 public:
  explicit MessageOneofFieldGenerator(const FieldDescriptor* descriptor,
                                      const Params& params);
  ~MessageOneofFieldGenerator();

  // implements FieldGenerator ---------------------------------------
  void GenerateMembers(io::Printer* printer, bool lazy_init) const;
  void GenerateClearCode(io::Printer* printer) const;
  void GenerateMergingCode(io::Printer* printer) const;
  void GenerateSerializationCode(io::Printer* printer) const;
  void GenerateSerializedSizeCode(io::Printer* printer) const;
  void GenerateEqualsCode(io::Printer* printer) const;
  void GenerateHashCodeCode(io::Printer* printer) const;
  void GenerateFixClonedCode(io::Printer* printer) const;

 private:
  const FieldDescriptor* descriptor_;
  map<string, string> variables_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(MessageOneofFieldGenerator);
};

class RepeatedMessageFieldGenerator : public FieldGenerator {
 public:
  explicit RepeatedMessageFieldGenerator(const FieldDescriptor* descriptor,
        const Params& params);
  ~RepeatedMessageFieldGenerator();

  // implements FieldGenerator ---------------------------------------
  void GenerateMembers(io::Printer* printer, bool lazy_init) const;
  void GenerateClearCode(io::Printer* printer) const;
  void GenerateMergingCode(io::Printer* printer) const;
  void GenerateSerializationCode(io::Printer* printer) const;
  void GenerateSerializedSizeCode(io::Printer* printer) const;
  void GenerateEqualsCode(io::Printer* printer) const;
  void GenerateHashCodeCode(io::Printer* printer) const;
  void GenerateFixClonedCode(io::Printer* printer) const;

 private:
  const FieldDescriptor* descriptor_;
  map<string, string> variables_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(RepeatedMessageFieldGenerator);
};

}  // namespace javanano
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_JAVANANO_MESSAGE_FIELD_H__
