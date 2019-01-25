
#ifndef GOOGLE_PROTOBUF_COMPILER_OBJECTIVEC_PRIMITIVE_FIELD_H__
#define GOOGLE_PROTOBUF_COMPILER_OBJECTIVEC_PRIMITIVE_FIELD_H__

#include <map>
#include <string>
#include <google/protobuf/compiler/objectivec/objectivec_field.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace objectivec {

class PrimitiveFieldGenerator : public SingleFieldGenerator {
  friend FieldGenerator* FieldGenerator::Make(const FieldDescriptor* field,
                                              const Options& options);

 protected:
  PrimitiveFieldGenerator(const FieldDescriptor* descriptor,
                          const Options& options);
  virtual ~PrimitiveFieldGenerator();

  virtual void GenerateFieldStorageDeclaration(io::Printer* printer) const;

  virtual int ExtraRuntimeHasBitsNeeded(void) const;
  virtual void SetExtraRuntimeHasBitsBase(int index_base);

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(PrimitiveFieldGenerator);
};

class PrimitiveObjFieldGenerator : public ObjCObjFieldGenerator {
  friend FieldGenerator* FieldGenerator::Make(const FieldDescriptor* field,
                                              const Options& options);

 protected:
  PrimitiveObjFieldGenerator(const FieldDescriptor* descriptor,
                             const Options& options);
  virtual ~PrimitiveObjFieldGenerator();

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(PrimitiveObjFieldGenerator);
};

class RepeatedPrimitiveFieldGenerator : public RepeatedFieldGenerator {
  friend FieldGenerator* FieldGenerator::Make(const FieldDescriptor* field,
                                              const Options& options);

 protected:
  RepeatedPrimitiveFieldGenerator(const FieldDescriptor* descriptor,
                                  const Options& options);
  virtual ~RepeatedPrimitiveFieldGenerator();

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(RepeatedPrimitiveFieldGenerator);
};

}  // namespace objectivec
}  // namespace compiler
}  // namespace protobuf
}  // namespace google

#endif  // GOOGLE_PROTOBUF_COMPILER_OBJECTIVEC_PRIMITIVE_FIELD_H__
