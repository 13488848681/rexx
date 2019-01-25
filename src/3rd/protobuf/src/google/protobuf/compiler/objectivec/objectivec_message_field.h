
#ifndef GOOGLE_PROTOBUF_COMPILER_OBJECTIVEC_MESSAGE_FIELD_H__
#define GOOGLE_PROTOBUF_COMPILER_OBJECTIVEC_MESSAGE_FIELD_H__

#include <map>
#include <string>
#include <google/protobuf/compiler/objectivec/objectivec_field.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace objectivec {

class MessageFieldGenerator : public ObjCObjFieldGenerator {
  friend FieldGenerator* FieldGenerator::Make(const FieldDescriptor* field,
                                              const Options& options);

 protected:
  MessageFieldGenerator(const FieldDescriptor* descriptor,
                        const Options& options);
  virtual ~MessageFieldGenerator();
  virtual bool WantsHasProperty(void) const;

 public:
  virtual void DetermineForwardDeclarations(set<string>* fwd_decls) const;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(MessageFieldGenerator);
};

class RepeatedMessageFieldGenerator : public RepeatedFieldGenerator {
  friend FieldGenerator* FieldGenerator::Make(const FieldDescriptor* field,
                                              const Options& options);

 protected:
  RepeatedMessageFieldGenerator(const FieldDescriptor* descriptor,
                                const Options& options);
  virtual ~RepeatedMessageFieldGenerator();

 public:
  virtual void DetermineForwardDeclarations(set<string>* fwd_decls) const;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(RepeatedMessageFieldGenerator);
};

}  // namespace objectivec
}  // namespace compiler
}  // namespace protobuf
}  // namespace google

#endif  // GOOGLE_PROTOBUF_COMPILER_OBJECTIVEC_MESSAGE_FIELD_H__
