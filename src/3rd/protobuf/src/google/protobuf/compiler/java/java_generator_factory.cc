#include <google/protobuf/compiler/java/java_generator_factory.h>

#include <google/protobuf/compiler/java/java_context.h>
#include <google/protobuf/compiler/java/java_enum_field.h>
#include <google/protobuf/compiler/java/java_extension.h>
#include <google/protobuf/compiler/java/java_extension_lite.h>
#include <google/protobuf/compiler/java/java_field.h>
#include <google/protobuf/compiler/java/java_helpers.h>
#include <google/protobuf/compiler/java/java_message.h>
#include <google/protobuf/compiler/java/java_message_lite.h>
#include <google/protobuf/compiler/java/java_service.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace java {

GeneratorFactory::GeneratorFactory() {}
GeneratorFactory::~GeneratorFactory() {}

// ===================================================================

ImmutableGeneratorFactory::ImmutableGeneratorFactory(
    Context* context) : context_(context) {
}
ImmutableGeneratorFactory::~ImmutableGeneratorFactory() {}

MessageGenerator* ImmutableGeneratorFactory::NewMessageGenerator(
    const Descriptor* descriptor) const {
  if (HasDescriptorMethods(descriptor, context_->EnforceLite())) {
    return new ImmutableMessageGenerator(descriptor, context_);
  } else {
    return new ImmutableMessageLiteGenerator(descriptor, context_);
  }
}

ExtensionGenerator* ImmutableGeneratorFactory::NewExtensionGenerator(
    const FieldDescriptor* descriptor) const {
  if (HasDescriptorMethods(descriptor->file(), context_->EnforceLite())) {
    return new ImmutableExtensionGenerator(descriptor, context_);
  } else {
    return new ImmutableExtensionLiteGenerator(descriptor, context_);
  }
}

ServiceGenerator* ImmutableGeneratorFactory::NewServiceGenerator(
    const ServiceDescriptor* descriptor) const {
  return new ImmutableServiceGenerator(descriptor, context_);
}


}  // namespace java
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
