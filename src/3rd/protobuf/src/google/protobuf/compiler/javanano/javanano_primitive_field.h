
#ifndef GOOGLE_PROTOBUF_COMPILER_JAVANANO_PRIMITIVE_FIELD_H__
#define GOOGLE_PROTOBUF_COMPILER_JAVANANO_PRIMITIVE_FIELD_H__

#include <map>
#include <string>
#include <google/protobuf/compiler/javanano/javanano_field.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace javanano {

class PrimitiveFieldGenerator : public FieldGenerator {
 public:
  explicit PrimitiveFieldGenerator(
      const FieldDescriptor* descriptor, const Params& params);
  ~PrimitiveFieldGenerator();

  // implements FieldGenerator ---------------------------------------
  bool SavedDefaultNeeded() const;
  void GenerateInitSavedDefaultCode(io::Printer* printer) const;
  void GenerateMembers(io::Printer* printer, bool lazy_init) const;
  void GenerateClearCode(io::Printer* printer) const;
  void GenerateMergingCode(io::Printer* printer) const;
  void GenerateSerializationCode(io::Printer* printer) const;
  void GenerateSerializedSizeCode(io::Printer* printer) const;
  void GenerateEqualsCode(io::Printer* printer) const;
  void GenerateHashCodeCode(io::Printer* printer) const;

 private:
  void GenerateSerializationConditional(io::Printer* printer) const;

  const FieldDescriptor* descriptor_;
  map<string, string> variables_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(PrimitiveFieldGenerator);
};

class AccessorPrimitiveFieldGenerator : public FieldGenerator {
 public:
  explicit AccessorPrimitiveFieldGenerator(const FieldDescriptor* descriptor,
      const Params &params, int has_bit_index);
  ~AccessorPrimitiveFieldGenerator();

  // implements FieldGenerator ---------------------------------------
  bool SavedDefaultNeeded() const;
  void GenerateInitSavedDefaultCode(io::Printer* printer) const;
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

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(AccessorPrimitiveFieldGenerator);
};

class PrimitiveOneofFieldGenerator : public FieldGenerator {
 public:
  explicit PrimitiveOneofFieldGenerator(
      const FieldDescriptor* descriptor, const Params& params);
  ~PrimitiveOneofFieldGenerator();

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

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(PrimitiveOneofFieldGenerator);
};

class RepeatedPrimitiveFieldGenerator : public FieldGenerator {
 public:
  explicit RepeatedPrimitiveFieldGenerator(const FieldDescriptor* descriptor,
                                           const Params& params);
  ~RepeatedPrimitiveFieldGenerator();

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

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(RepeatedPrimitiveFieldGenerator);
};

}  // namespace javanano
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_JAVANANO_PRIMITIVE_FIELD_H__
