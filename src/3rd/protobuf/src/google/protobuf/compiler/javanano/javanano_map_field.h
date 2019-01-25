
#ifndef GOOGLE_PROTOBUF_COMPILER_JAVANANO_MAP_FIELD_H__
#define GOOGLE_PROTOBUF_COMPILER_JAVANANO_MAP_FIELD_H__

#include <map>
#include <string>
#include <vector>
#include <google/protobuf/compiler/javanano/javanano_field.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace javanano {

class MapFieldGenerator : public FieldGenerator {
 public:
  explicit MapFieldGenerator(
      const FieldDescriptor* descriptor, const Params& params);
  ~MapFieldGenerator();

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

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(MapFieldGenerator);
};

}  // namespace javanano
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_JAVANANO_MAP_FIELD_H__
