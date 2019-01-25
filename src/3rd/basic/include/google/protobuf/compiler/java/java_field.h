
#ifndef GOOGLE_PROTOBUF_COMPILER_JAVA_FIELD_H__
#define GOOGLE_PROTOBUF_COMPILER_JAVA_FIELD_H__

#include <map>
#include <memory>
#ifndef _SHARED_PTR_H
#include <google/protobuf/stubs/shared_ptr.h>
#endif
#include <string>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/stubs/logging.h>

namespace google {
namespace protobuf {
  namespace compiler {
    namespace java {
      class Context;                // context.h
      class ClassNameResolver;      // name_resolver.h
    }
  }
  namespace io {
    class Printer;                  // printer.h
  }
}

namespace protobuf {
namespace compiler {
namespace java {

class ImmutableFieldGenerator {
 public:
  ImmutableFieldGenerator() {}
  virtual ~ImmutableFieldGenerator();

  virtual int GetNumBitsForMessage() const = 0;
  virtual int GetNumBitsForBuilder() const = 0;
  virtual void GenerateInterfaceMembers(io::Printer* printer) const = 0;
  virtual void GenerateMembers(io::Printer* printer) const = 0;
  virtual void GenerateBuilderMembers(io::Printer* printer) const = 0;
  virtual void GenerateInitializationCode(io::Printer* printer) const = 0;
  virtual void GenerateBuilderClearCode(io::Printer* printer) const = 0;
  virtual void GenerateMergingCode(io::Printer* printer) const = 0;
  virtual void GenerateBuildingCode(io::Printer* printer) const = 0;
  virtual void GenerateParsingCode(io::Printer* printer) const = 0;
  virtual void GenerateParsingCodeFromPacked(io::Printer* printer) const;
  virtual void GenerateParsingDoneCode(io::Printer* printer) const = 0;
  virtual void GenerateSerializationCode(io::Printer* printer) const = 0;
  virtual void GenerateSerializedSizeCode(io::Printer* printer) const = 0;
  virtual void GenerateFieldBuilderInitializationCode(io::Printer* printer)
      const = 0;

  virtual void GenerateEqualsCode(io::Printer* printer) const = 0;
  virtual void GenerateHashCode(io::Printer* printer) const = 0;

  virtual string GetBoxedType() const = 0;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ImmutableFieldGenerator);
};

class ImmutableFieldLiteGenerator {
 public:
  ImmutableFieldLiteGenerator() {}
  virtual ~ImmutableFieldLiteGenerator();

  virtual int GetNumBitsForMessage() const = 0;
  virtual int GetNumBitsForBuilder() const = 0;
  virtual void GenerateInterfaceMembers(io::Printer* printer) const = 0;
  virtual void GenerateMembers(io::Printer* printer) const = 0;
  virtual void GenerateBuilderMembers(io::Printer* printer) const = 0;
  virtual void GenerateInitializationCode(io::Printer* printer) const = 0;
  virtual void GenerateVisitCode(io::Printer* printer) const = 0;
  virtual void GenerateDynamicMethodMakeImmutableCode(io::Printer* printer)
      const = 0;
  virtual void GenerateParsingCode(io::Printer* printer) const = 0;
  virtual void GenerateParsingCodeFromPacked(io::Printer* printer) const;
  virtual void GenerateParsingDoneCode(io::Printer* printer) const = 0;
  virtual void GenerateSerializationCode(io::Printer* printer) const = 0;
  virtual void GenerateSerializedSizeCode(io::Printer* printer) const = 0;
  virtual void GenerateFieldBuilderInitializationCode(io::Printer* printer)
      const = 0;

  virtual void GenerateEqualsCode(io::Printer* printer) const = 0;
  virtual void GenerateHashCode(io::Printer* printer) const = 0;

  virtual string GetBoxedType() const = 0;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ImmutableFieldLiteGenerator);
};


// Convenience class which constructs FieldGenerators for a Descriptor.
template<typename FieldGeneratorType>
class FieldGeneratorMap {
 public:
  explicit FieldGeneratorMap(const Descriptor* descriptor,
                             Context* context);
  ~FieldGeneratorMap();

  const FieldGeneratorType& get(const FieldDescriptor* field) const;

 private:
  const Descriptor* descriptor_;
  Context* context_;
  ClassNameResolver* name_resolver_;
  google::protobuf::scoped_array<google::protobuf::scoped_ptr<FieldGeneratorType> > field_generators_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(FieldGeneratorMap);
};

template<typename FieldGeneratorType>
inline const FieldGeneratorType&
FieldGeneratorMap<FieldGeneratorType>::get(const FieldDescriptor* field) const {
  GOOGLE_CHECK_EQ(field->containing_type(), descriptor_);
  return *field_generators_[field->index()];
}

// Instantiate template for mutable and immutable maps.
template<>
FieldGeneratorMap<ImmutableFieldGenerator>::
FieldGeneratorMap(const Descriptor* descriptor,
                  Context* context);

template<>
FieldGeneratorMap<ImmutableFieldGenerator>::~FieldGeneratorMap();


// Field information used in FieldGeneartors.
struct FieldGeneratorInfo {
  string name;
  string capitalized_name;
  string disambiguated_reason;
};

// Oneof information used in OneofFieldGeneartors.
struct OneofGeneratorInfo {
  string name;
  string capitalized_name;
};

// Set some common variables used in variable FieldGenerators.
void SetCommonFieldVariables(const FieldDescriptor* descriptor,
                             const FieldGeneratorInfo* info,
                             map<string, string>* variables);

// Set some common oneof variables used in OneofFieldGenerators.
void SetCommonOneofVariables(const FieldDescriptor* descriptor,
                             const OneofGeneratorInfo* info,
                             map<string, string>* variables);

// Print useful comments before a field's accessors.
void PrintExtraFieldInfo(const map<string, string>& variables,
                         io::Printer* printer);

}  // namespace java
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_JAVA_FIELD_H__
