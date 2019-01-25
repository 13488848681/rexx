
#ifndef GOOGLE_PROTOBUF_COMPILER_CPP_MAP_FIELD_H__
#define GOOGLE_PROTOBUF_COMPILER_CPP_MAP_FIELD_H__

#include <map>
#include <string>

#include <google/protobuf/compiler/cpp/cpp_message_field.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace cpp {

class MapFieldGenerator : public FieldGenerator {
 public:
  MapFieldGenerator(const FieldDescriptor* descriptor, const Options& options);
  ~MapFieldGenerator();

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
  // A helper for GenerateSerializeWithCachedSizes{,ToArray}.
  void GenerateSerializeWithCachedSizes(
      io::Printer* printer, const map<string, string>& variables) const;

  const FieldDescriptor* descriptor_;
  const bool dependent_field_;
  map<string, string> variables_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(MapFieldGenerator);
};

}  // namespace cpp
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_CPP_MAP_FIELD_H__
