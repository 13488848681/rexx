#ifndef GOOGLE_PROTOBUF_COMPILER_JAVA_GENERATOR_FACTORY_H__
#define GOOGLE_PROTOBUF_COMPILER_JAVA_GENERATOR_FACTORY_H__

#include <google/protobuf/stubs/common.h>

namespace google {
namespace protobuf {
  class FieldDescriptor;         // descriptor.h
  class Descriptor;              // descriptor.h
  class ServiceDescriptor;       // descriptor.h
  namespace compiler {
    namespace java {
      class MessageGenerator;    // message.h
      class ExtensionGenerator;  // extension.h
      class ServiceGenerator;    // service.h
      class Context;             // context.h
    }
  }
}

namespace protobuf {
namespace compiler {
namespace java {

class GeneratorFactory {
 public:
  GeneratorFactory();
  virtual ~GeneratorFactory();

  virtual MessageGenerator* NewMessageGenerator(
      const Descriptor* descriptor) const = 0;

  virtual ExtensionGenerator* NewExtensionGenerator(
      const FieldDescriptor* descriptor) const = 0;

  virtual ServiceGenerator* NewServiceGenerator(
      const ServiceDescriptor* descriptor) const = 0;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(GeneratorFactory);
};

// Factory that creates generators for immutable-default messages.
class ImmutableGeneratorFactory : public GeneratorFactory {
 public:
  ImmutableGeneratorFactory(Context* context);
  virtual ~ImmutableGeneratorFactory();

  virtual MessageGenerator* NewMessageGenerator(
      const Descriptor* descriptor) const;

  virtual ExtensionGenerator* NewExtensionGenerator(
      const FieldDescriptor* descriptor) const;

  virtual ServiceGenerator* NewServiceGenerator(
      const ServiceDescriptor* descriptor) const;

 private:
  Context* context_;
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ImmutableGeneratorFactory);
};


}  // namespace java
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_JAVA_GENERATOR_FACTORY_H__
