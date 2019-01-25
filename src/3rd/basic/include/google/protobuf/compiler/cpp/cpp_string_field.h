
#ifndef GOOGLE_PROTOBUF_COMPILER_CPP_STRING_FIELD_H__
#define GOOGLE_PROTOBUF_COMPILER_CPP_STRING_FIELD_H__

#include <map>
#include <string>
#include <google/protobuf/compiler/cpp/cpp_field.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace cpp {

class StringFieldGenerator : public FieldGenerator {
 public:
  StringFieldGenerator(const FieldDescriptor* descriptor,
                       const Options& options);
  ~StringFieldGenerator();

  // implements FieldGenerator ---------------------------------------
  void GeneratePrivateMembers(io::Printer* printer) const;
  void GenerateStaticMembers(io::Printer* printer) const;
  void GenerateAccessorDeclarations(io::Printer* printer) const;
  void GenerateInlineAccessorDefinitions(io::Printer* printer,
                                         bool is_inline) const;
  void GenerateNonInlineAccessorDefinitions(io::Printer* printer) const;
  void GenerateClearingCode(io::Printer* printer) const;
  void GenerateMergingCode(io::Printer* printer) const;
  void GenerateSwappingCode(io::Printer* printer) const;
  void GenerateConstructorCode(io::Printer* printer) const;
  void GenerateDestructorCode(io::Printer* printer) const;
  void GenerateDefaultInstanceAllocator(io::Printer* printer) const;
  void GenerateShutdownCode(io::Printer* printer) const;
  void GenerateMergeFromCodedStream(io::Printer* printer) const;
  void GenerateSerializeWithCachedSizes(io::Printer* printer) const;
  void GenerateSerializeWithCachedSizesToArray(io::Printer* printer) const;
  void GenerateByteSize(io::Printer* printer) const;

 protected:
  const FieldDescriptor* descriptor_;
  map<string, string> variables_;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(StringFieldGenerator);
};

class StringOneofFieldGenerator : public StringFieldGenerator {
 public:
  StringOneofFieldGenerator(const FieldDescriptor* descriptor,
                            const Options& options);
  ~StringOneofFieldGenerator();

  // implements FieldGenerator ---------------------------------------
  void GenerateInlineAccessorDefinitions(io::Printer* printer,
                                         bool is_inline) const;
  void GenerateClearingCode(io::Printer* printer) const;
  void GenerateSwappingCode(io::Printer* printer) const;
  void GenerateConstructorCode(io::Printer* printer) const;
  void GenerateDestructorCode(io::Printer* printer) const;
  void GenerateMergeFromCodedStream(io::Printer* printer) const;

 private:
  const bool dependent_field_;
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(StringOneofFieldGenerator);
};

class RepeatedStringFieldGenerator : public FieldGenerator {
 public:
  RepeatedStringFieldGenerator(const FieldDescriptor* descriptor,
                               const Options& options);
  ~RepeatedStringFieldGenerator();

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

 private:
  const FieldDescriptor* descriptor_;
  map<string, string> variables_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(RepeatedStringFieldGenerator);
};

}  // namespace cpp
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_CPP_STRING_FIELD_H__
