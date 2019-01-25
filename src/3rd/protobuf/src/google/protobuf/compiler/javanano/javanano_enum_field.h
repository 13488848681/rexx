
#ifndef GOOGLE_PROTOBUF_COMPILER_JAVANANO_ENUM_FIELD_H__
#define GOOGLE_PROTOBUF_COMPILER_JAVANANO_ENUM_FIELD_H__

#include <map>
#include <string>
#include <vector>
#include <google/protobuf/compiler/javanano/javanano_field.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace javanano {

class EnumFieldGenerator : public FieldGenerator {
 public:
  explicit EnumFieldGenerator(
      const FieldDescriptor* descriptor, const Params& params);
  ~EnumFieldGenerator();

  // implements FieldGenerator ---------------------------------------
  void GenerateMembers(io::Printer* printer, bool lazy_init) const;
  void GenerateClearCode(io::Printer* printer) const;
  void GenerateMergingCode(io::Printer* printer) const;
  void GenerateSerializationCode(io::Printer* printer) const;
  void GenerateSerializedSizeCode(io::Printer* printer) const;
  void GenerateEqualsCode(io::Printer* printer) const;
  void GenerateHashCodeCode(io::Printer* printer) const;

 private:
  const FieldDescriptor* descriptor_;
  map<string, string> variables_;
  vector<string> canonical_values_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(EnumFieldGenerator);
};

class AccessorEnumFieldGenerator : public FieldGenerator {
 public:
  explicit AccessorEnumFieldGenerator(const FieldDescriptor* descriptor,
      const Params& params, int has_bit_index);
  ~AccessorEnumFieldGenerator();

  // implements FieldGenerator ---------------------------------------
  void GenerateMembers(io::Printer* printer, bool lazy_init) const;
  void GenerateClearCode(io::Printer* printer) const;
  void GenerateMergingCode(io::Printer* printer) const;
  void GenerateSerializationCode(io::Printer* printer) const;
  void GenerateSerializedSizeCode(io::Printer* printer) const;
  void GenerateEqualsCode(io::Printer* printer) const;
  void GenerateHashCodeCode(io::Printer* printer) const;

 private:
  const FieldDescriptor* descriptor_;
  map<string, string> variables_;
  vector<string> canonical_values_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(AccessorEnumFieldGenerator);
};

class RepeatedEnumFieldGenerator : public FieldGenerator {
 public:
  explicit RepeatedEnumFieldGenerator(
      const FieldDescriptor* descriptor, const Params& params);
  ~RepeatedEnumFieldGenerator();

  // implements FieldGenerator ---------------------------------------
  void GenerateMembers(io::Printer* printer, bool lazy_init) const;
  void GenerateClearCode(io::Printer* printer) const;
  void GenerateMergingCode(io::Printer* printer) const;
  void GenerateMergingCodeFromPacked(io::Printer* printer) const;
  void GenerateSerializationCode(io::Printer* printer) const;
  void GenerateSerializedSizeCode(io::Printer* printer) const;
  void GenerateEqualsCode(io::Printer* printer) const;
  void GenerateHashCodeCode(io::Printer* printer) const;
  void GenerateFixClonedCode(io::Printer* printer) const;

 private:
  void GenerateRepeatedDataSizeCode(io::Printer* printer) const;

  const FieldDescriptor* descriptor_;
  map<string, string> variables_;
  vector<string> canonical_values_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(RepeatedEnumFieldGenerator);
};

}  // namespace javanano
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_JAVANANO_ENUM_FIELD_H__
