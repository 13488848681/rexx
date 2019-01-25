
#ifndef GOOGLE_PROTOBUF_COMPILER_JAVA_SERVICE_H__
#define GOOGLE_PROTOBUF_COMPILER_JAVA_SERVICE_H__

#include <map>
#include <google/protobuf/descriptor.h>

namespace google {
namespace protobuf {
  namespace compiler {
    namespace java {
      class Context;            // context.h
      class ClassNameResolver;  // name_resolver.h
    }
  }
  namespace io {
    class Printer;              // printer.h
  }
}

namespace protobuf {
namespace compiler {
namespace java {

class ServiceGenerator {
 public:
  explicit ServiceGenerator(const ServiceDescriptor* descriptor);
  virtual ~ServiceGenerator();

  virtual void Generate(io::Printer* printer) = 0;

  enum RequestOrResponse { REQUEST, RESPONSE };
  enum IsAbstract { IS_ABSTRACT, IS_CONCRETE };

 protected:
  const ServiceDescriptor* descriptor_;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ServiceGenerator);
};

class ImmutableServiceGenerator : public ServiceGenerator {
 public:
  ImmutableServiceGenerator(const ServiceDescriptor* descriptor,
                            Context* context);
  virtual ~ImmutableServiceGenerator();

  virtual void Generate(io::Printer* printer);

 private:

  // Generate the getDescriptorForType() method.
  void GenerateGetDescriptorForType(io::Printer* printer);

  // Generate a Java interface for the service.
  void GenerateInterface(io::Printer* printer);

  // Generate newReflectiveService() method.
  void GenerateNewReflectiveServiceMethod(io::Printer* printer);

  // Generate newReflectiveBlockingService() method.
  void GenerateNewReflectiveBlockingServiceMethod(io::Printer* printer);

  // Generate abstract method declarations for all methods.
  void GenerateAbstractMethods(io::Printer* printer);

  // Generate the implementation of Service.callMethod().
  void GenerateCallMethod(io::Printer* printer);

  // Generate the implementation of BlockingService.callBlockingMethod().
  void GenerateCallBlockingMethod(io::Printer* printer);

  // Generate the implementations of Service.get{Request,Response}Prototype().
  void GenerateGetPrototype(RequestOrResponse which, io::Printer* printer);

  // Generate a stub implementation of the service.
  void GenerateStub(io::Printer* printer);

  // Generate a method signature, possibly abstract, without body or trailing
  // semicolon.
  void GenerateMethodSignature(io::Printer* printer,
                               const MethodDescriptor* method,
                               IsAbstract is_abstract);

  // Generate a blocking stub interface and implementation of the service.
  void GenerateBlockingStub(io::Printer* printer);

  // Generate the method signature for one method of a blocking stub.
  void GenerateBlockingMethodSignature(io::Printer* printer,
                                       const MethodDescriptor* method);

  Context* context_;
  ClassNameResolver* name_resolver_;
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ImmutableServiceGenerator);
};

}  // namespace java
}  // namespace compiler
}  // namespace protobuf

#endif  // NET_PROTO2_COMPILER_JAVA_SERVICE_H__
}  // namespace google
