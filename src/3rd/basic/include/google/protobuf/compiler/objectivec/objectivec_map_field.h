
#ifndef GOOGLE_PROTOBUF_COMPILER_OBJECTIVEC_MAP_FIELD_H__
#define GOOGLE_PROTOBUF_COMPILER_OBJECTIVEC_MAP_FIELD_H__

#include <map>
#include <string>
#include <google/protobuf/compiler/objectivec/objectivec_field.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace objectivec {

class MapFieldGenerator : public RepeatedFieldGenerator {
  friend FieldGenerator* FieldGenerator::Make(const FieldDescriptor* field,
                                              const Options& options);

 public:
  virtual void FinishInitialization(void);

 protected:
  MapFieldGenerator(const FieldDescriptor* descriptor, const Options& options);
  virtual ~MapFieldGenerator();

  virtual void DetermineForwardDeclarations(set<string>* fwd_decls) const;

 private:
  scoped_ptr<FieldGenerator> value_field_generator_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(MapFieldGenerator);
};

}  // namespace objectivec
}  // namespace compiler
}  // namespace protobuf
}  // namespace google

#endif  // GOOGLE_PROTOBUF_COMPILER_OBJECTIVEC_MAP_FIELD_H__
