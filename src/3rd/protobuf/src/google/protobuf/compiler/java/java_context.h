#ifndef GOOGLE_PROTOBUF_COMPILER_JAVA_CONTEXT_H__
#define GOOGLE_PROTOBUF_COMPILER_JAVA_CONTEXT_H__

#include <map>
#include <memory>
#ifndef _SHARED_PTR_H
#include <google/protobuf/stubs/shared_ptr.h>
#endif
#include <vector>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/compiler/java/java_options.h>

namespace google {
namespace protobuf {
  class FileDescriptor;
  class FieldDescriptor;
  class OneofDescriptor;
  class Descriptor;
  class EnumDescriptor;
  namespace compiler {
    namespace java {
      class ClassNameResolver;  // name_resolver.h
    }
  }
}  // namespace protobuf

namespace protobuf {
namespace compiler {
namespace java {

struct FieldGeneratorInfo;
struct OneofGeneratorInfo;
// A context object holds the information that is shared among all code
// generators.
class Context {
 public:
  Context(const FileDescriptor* file, const Options& options);
  ~Context();

  // Get the name resolver associated with this context. The resolver
  // can be used to map descriptors to Java class names.
  ClassNameResolver* GetNameResolver();

  // Get the FieldGeneratorInfo for a given field.
  const FieldGeneratorInfo* GetFieldGeneratorInfo(
      const FieldDescriptor* field) const;

  // Get the OneofGeneratorInfo for a given oneof.
  const OneofGeneratorInfo* GetOneofGeneratorInfo(
      const OneofDescriptor* oneof) const;

  const Options& options() const { return options_; }

  // Enforces all the files (including transitive dependencies) to use
  // LiteRuntime.

  bool EnforceLite() const { return options_.enforce_lite; }

  // Does this message class have generated parsing, serialization, and other
  // standard methods for which reflection-based fallback implementations exist?
  bool HasGeneratedMethods(const Descriptor* descriptor) const;

 private:
  void InitializeFieldGeneratorInfo(const FileDescriptor* file);
  void InitializeFieldGeneratorInfoForMessage(const Descriptor* message);
  void InitializeFieldGeneratorInfoForFields(
      const vector<const FieldDescriptor*>& fields);

  google::protobuf::scoped_ptr<ClassNameResolver> name_resolver_;
  map<const FieldDescriptor*, FieldGeneratorInfo> field_generator_info_map_;
  map<const OneofDescriptor*, OneofGeneratorInfo> oneof_generator_info_map_;
  Options options_;
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(Context);
};

}  // namespace java
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_JAVA_CONTEXT_H__
