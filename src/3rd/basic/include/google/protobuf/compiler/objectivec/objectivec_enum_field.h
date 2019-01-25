
#ifndef GOOGLE_PROTOBUF_COMPILER_OBJECTIVEC_ENUM_FIELD_H__
#define GOOGLE_PROTOBUF_COMPILER_OBJECTIVEC_ENUM_FIELD_H__

#include <map>
#include <string>
#include <google/protobuf/compiler/objectivec/objectivec_field.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace objectivec {

class EnumFieldGenerator : public SingleFieldGenerator {
  friend FieldGenerator* FieldGenerator::Make(const FieldDescriptor* field,
                                              const Options& options);

 public:
  virtual void GenerateCFunctionDeclarations(io::Printer* printer) const;
  virtual void GenerateCFunctionImplementations(io::Printer* printer) const;
  virtual void DetermineForwardDeclarations(set<string>* fwd_decls) const;

 protected:
  EnumFieldGenerator(const FieldDescriptor* descriptor, const Options& options);
  virtual ~EnumFieldGenerator();

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(EnumFieldGenerator);
};

class RepeatedEnumFieldGenerator : public RepeatedFieldGenerator {
  friend FieldGenerator* FieldGenerator::Make(const FieldDescriptor* field,
                                              const Options& options);

 public:
  virtual void FinishInitialization();

 protected:
  RepeatedEnumFieldGenerator(const FieldDescriptor* descriptor,
                             const Options& options);
  virtual ~RepeatedEnumFieldGenerator();

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(RepeatedEnumFieldGenerator);
};

}  // namespace objectivec
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_OBJECTIVEC_ENUM_FIELD_H__
