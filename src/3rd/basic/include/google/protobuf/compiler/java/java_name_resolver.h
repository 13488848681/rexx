
#ifndef GOOGLE_PROTOBUF_COMPILER_JAVA_NAME_RESOLVER_H__
#define GOOGLE_PROTOBUF_COMPILER_JAVA_NAME_RESOLVER_H__

#include <map>
#include <string>

#include <google/protobuf/stubs/common.h>

namespace google {
namespace protobuf {
class Descriptor;
class EnumDescriptor;
class FieldDescriptor;
class FileDescriptor;
class ServiceDescriptor;

namespace compiler {
namespace java {

// Used to get the Java class related names for a given descriptor. It caches
// the results to avoid redundant calculation across multiple name queries.
// Thread-safety note: This class is *not* thread-safe.
class ClassNameResolver {
 public:
  ClassNameResolver();
  ~ClassNameResolver();

  // Gets the unqualified outer class name for the file.
  string GetFileClassName(const FileDescriptor* file, bool immutable);
  // Gets the unqualified immutable outer class name of a file.
  string GetFileImmutableClassName(const FileDescriptor* file);
  // Gets the unqualified default immutable outer class name of a file
  // (converted from the proto file's name).
  string GetFileDefaultImmutableClassName(const FileDescriptor* file);

  // Check whether there is any type defined in the proto file that has
  // the given class name.
  bool HasConflictingClassName(const FileDescriptor* file,
                               const string& classname);

  // Gets the name of the outer class that holds descriptor information.
  // Descriptors are shared between immutable messages and mutable messages.
  // Since both of them are generated optionally, the descriptors need to be
  // put in another common place.
  string GetDescriptorClassName(const FileDescriptor* file);

  // Gets the fully-qualified class name corresponding to the given descriptor.
  string GetClassName(const Descriptor* descriptor, bool immutable);
  string GetClassName(const EnumDescriptor* descriptor, bool immutable);
  string GetClassName(const ServiceDescriptor* descriptor, bool immutable);
  string GetClassName(const FileDescriptor* descriptor, bool immutable);

  template<class DescriptorType>
  string GetImmutableClassName(const DescriptorType* descriptor) {
    return GetClassName(descriptor, true);
  }
  template<class DescriptorType>
  string GetMutableClassName(const DescriptorType* descriptor) {
    return GetClassName(descriptor, false);
  }

  // Gets the fully qualified name of an extension identifier.
  string GetExtensionIdentifierName(const FieldDescriptor* descriptor,
                                    bool immutable);

  // Gets the fully qualified name for generated classes in Java convention.
  // Nested classes will be separated using '$' instead of '.'
  // For example:
  //   com.package.OuterClass$OuterMessage$InnerMessage
  string GetJavaImmutableClassName(const Descriptor* descriptor);
  string GetJavaImmutableClassName(const EnumDescriptor* descriptor);
 private:
  // Get the full name of a Java class by prepending the Java package name
  // or outer class name.
  string GetClassFullName(const string& name_without_package,
                          const FileDescriptor* file,
                          bool immutable,
                          bool multiple_files);
  // Get the Java Class style full name of a message.
  string GetJavaClassFullName(
      const string& name_without_package,
      const FileDescriptor* file,
      bool immutable);
  // Caches the result to provide better performance.
  map<const FileDescriptor*, string> file_immutable_outer_class_names_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ClassNameResolver);
};

}  // namespace java
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_JAVA_NAME_RESOLVER_H__
