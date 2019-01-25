
#ifndef GOOGLE_PROTOBUF_COMPILER_CPP_PRIMITIVE_FIELD_H__
#define GOOGLE_PROTOBUF_COMPILER_CPP_PRIMITIVE_FIELD_H__

#include <map>
#include <string>
#include <google/protobuf/compiler/cpp/cpp_field.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace cpp {

class PrimitiveFieldGenerator : public FieldGenerator {
 public:
  PrimitiveFieldGenerator(const FieldDescriptor* descriptor,
                          const Options& options);
  ~PrimitiveFieldGenerator();

  // implements FieldGenerator ---------------------------------------
  void GeneratePrivateMembers(io::Printer* printer) const;
  void GenerateAccessorDeclarations(io::Printer* printer) const;
  void GenerateInlineAccessorDefinitions(io::Printer* printer,
                                         bool is_inline) const;
  void GenerateClearingCode(io::Printer* printer) const;
  void GenerateMergingCode(io::Printer* printer) const;
  void GenerateSwappingCode(io::Printer* printer) const;
  void GenerateConstructorCode(io::Printer* printer) const;
  void GenerateMergeFromCodedStream(io::Printer* printer) const;
  void GenerateSerializeWithCachedSizes(io::Printer* printer) const;
  void GenerateSerializeWithCachedSizesToArray(io::Printer* printer) const;
  void GenerateByteSize(io::Printer* printer) const;

 protected:
  const FieldDescriptor* descriptor_;
  map<string, string> variables_;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(PrimitiveFieldGenerator);
};

class PrimitiveOneofFieldGenerator : public PrimitiveFieldGenerator {
 public:
  PrimitiveOneofFieldGenerator(const FieldDescriptor* descriptor,
                               const Options& options);
  ~PrimitiveOneofFieldGenerator();

  // implements FieldGenerator ---------------------------------------
  void GenerateInlineAccessorDefinitions(io::Printer* printer,
                                         bool is_inline) const;
  void GenerateClearingCode(io::Printer* printer) const;
  void GenerateSwappingCode(io::Printer* printer) const;
  void GenerateConstructorCode(io::Printer* printer) const;
  void GenerateMergeFromCodedStream(io::Printer* printer) const;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(PrimitiveOneofFieldGenerator);
};

class RepeatedPrimitiveFieldGenerator : public FieldGenerator {
 public:
  RepeatedPrimitiveFieldGenerator(const FieldDescriptor* descriptor,
                                  const Options& options);
  ~RepeatedPrimitiveFieldGenerator();

  // implements FieldGenerator ---------------------------------------
  void GeneratePrivateMembers(io::Printer* printer) const;
  void GenerateAccessorDeclarations(io::Printer* printer) const;
  void GenerateInlineAccessorDefinitions(io::Printer* printer,
                                         bool is_inline) const;
  void GenerateClearingCode(io::Printer* printer) const;
  void GenerateMergingCode(io::Printer* printer) const;
  void GenerateSwappingCode(io::Printer* printer) const;
  void GenerateConstructorCode(io::Printer* printer) const;
  void GenerateMergeFromCodedStream(io::Printer* printer) const;
  void GenerateMergeFromCodedStreamWithPacking(io::Printer* printer) const;
  void GenerateSerializeWithCachedSizes(io::Printer* printer) const;
  void GenerateSerializeWithCachedSizesToArray(io::Printer* printer) const;
  void GenerateByteSize(io::Printer* printer) const;

 private:
  const FieldDescriptor* descriptor_;
  map<string, string> variables_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(RepeatedPrimitiveFieldGenerator);
};

}  // namespace cpp
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_CPP_PRIMITIVE_FIELD_H__
