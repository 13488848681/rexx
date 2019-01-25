
#ifndef GOOGLE_PROTOBUF_COMPILER_CPP_ENUM_H__
#define GOOGLE_PROTOBUF_COMPILER_CPP_ENUM_H__

#include <map>
#include <set>
#include <string>
#include <google/protobuf/compiler/cpp/cpp_options.h>
#include <google/protobuf/descriptor.h>

namespace google {
namespace protobuf {
  namespace io {
    class Printer;             // printer.h
  }
}

namespace protobuf {
namespace compiler {
namespace cpp {

class EnumGenerator {
 public:
  // See generator.cc for the meaning of dllexport_decl.
  EnumGenerator(const EnumDescriptor* descriptor, const Options& options);
  ~EnumGenerator();

  // Header stuff.

  // Fills the name to use when declaring the enum. This is for use when
  // generating other .proto.h files. This code should be placed within the
  // enum's package namespace, but NOT within any class, even for nested
  // enums. A given key in enum_names will map from an enum class name to the
  // EnumDescriptor that was responsible for its inclusion in the map. This can
  // be used to associate the descriptor with the code generated for it.
  void FillForwardDeclaration(map<string, const EnumDescriptor*>* enum_names);

  // Generate header code defining the enum.  This code should be placed
  // within the enum's package namespace, but NOT within any class, even for
  // nested enums.
  void GenerateDefinition(io::Printer* printer);

  // Generate specialization of GetEnumDescriptor<MyEnum>().
  // Precondition: in ::google::protobuf namespace.
  void GenerateGetEnumDescriptorSpecializations(io::Printer* printer);

  // For enums nested within a message, generate code to import all the enum's
  // symbols (e.g. the enum type name, all its values, etc.) into the class's
  // namespace.  This should be placed inside the class definition in the
  // header.
  void GenerateSymbolImports(io::Printer* printer);

  // Source file stuff.

  // Generate code that initializes the global variable storing the enum's
  // descriptor.
  void GenerateDescriptorInitializer(io::Printer* printer, int index);

  // Generate non-inline methods related to the enum, such as IsValidValue().
  // Goes in the .cc file.
  void GenerateMethods(io::Printer* printer);

 private:
  const EnumDescriptor* descriptor_;
  const string classname_;
  const Options& options_;
  // whether to generate the *_ARRAYSIZE constant.
  const bool generate_array_size_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(EnumGenerator);
};

}  // namespace cpp
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_CPP_ENUM_H__
