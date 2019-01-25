
#ifndef GOOGLE_PROTOBUF_COMPILER_CPP_MESSAGE_FIELD_H__
#define GOOGLE_PROTOBUF_COMPILER_CPP_MESSAGE_FIELD_H__

#include <map>
#include <string>
#include <google/protobuf/compiler/cpp/cpp_field.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace cpp {

class MessageFieldGenerator : public FieldGenerator {
 public:
  MessageFieldGenerator(const FieldDescriptor* descriptor,
                        const Options& options);
  ~MessageFieldGenerator();

  // implements FieldGenerator ---------------------------------------
  void GeneratePrivateMembers(io::Printer* printer) const;
  void GenerateDependentAccessorDeclarations(io::Printer* printer) const;
  void GenerateAccessorDeclarations(io::Printer* printer) const;
  void GenerateDependentInlineAccessorDefinitions(io::Printer* printer) const;
  void GenerateInlineAccessorDefinitions(io::Printer* printer,
                                         bool is_inline) const;
  void GenerateNonInlineAccessorDefinitions(io::Printer* printer) const;
  void GenerateClearingCode(io::Printer* printer) const;
  void GenerateMergingCode(io::Printer* printer) const;
  void GenerateSwappingCode(io::Printer* printer) const;
  void GenerateConstructorCode(io::Printer* printer) const;
  void GenerateMergeFromCodedStream(io::Printer* printer) const;
  void GenerateSerializeWithCachedSizes(io::Printer* printer) const;
  void GenerateSerializeWithCachedSizesToArray(io::Printer* printer) const;
  void GenerateByteSize(io::Printer* printer) const;

 protected:
  void GenerateArenaManipulationCode(const map<string, string>& variables,
                                     io::Printer* printer) const;

  virtual void GenerateGetterDeclaration(io::Printer* printer) const;

  const FieldDescriptor* descriptor_;
  const bool dependent_field_;
  map<string, string> variables_;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(MessageFieldGenerator);
};

class MessageOneofFieldGenerator : public MessageFieldGenerator {
 public:
  MessageOneofFieldGenerator(const FieldDescriptor* descriptor,
                             const Options& options);
  ~MessageOneofFieldGenerator();

  // implements FieldGenerator ---------------------------------------
  void GenerateDependentAccessorDeclarations(io::Printer* printer) const;
  void GenerateDependentInlineAccessorDefinitions(io::Printer* printer) const;
  void GenerateInlineAccessorDefinitions(io::Printer* printer,
                                         bool is_inline) const;
  void GenerateNonInlineAccessorDefinitions(io::Printer* printer) const;
  void GenerateClearingCode(io::Printer* printer) const;
  void GenerateSwappingCode(io::Printer* printer) const;
  void GenerateConstructorCode(io::Printer* printer) const;

 protected:
  void GenerateGetterDeclaration(io::Printer* printer) const;

 private:
  void InternalGenerateInlineAccessorDefinitions(
      const map<string, string>& variables, io::Printer* printer) const;

  const bool dependent_base_;
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(MessageOneofFieldGenerator);
};

class RepeatedMessageFieldGenerator : public FieldGenerator {
 public:
  RepeatedMessageFieldGenerator(const FieldDescriptor* descriptor,
                                const Options& options);
  ~RepeatedMessageFieldGenerator();

  // implements FieldGenerator ---------------------------------------
  void GeneratePrivateMembers(io::Printer* printer) const;
  void GenerateDependentAccessorDeclarations(io::Printer* printer) const;
  void GenerateAccessorDeclarations(io::Printer* printer) const;
  void GenerateDependentInlineAccessorDefinitions(io::Printer* printer) const;
  void GenerateInlineAccessorDefinitions(io::Printer* printer,
                                         bool is_inline) const;
  void GenerateClearingCode(io::Printer* printer) const;
  void GenerateMergingCode(io::Printer* printer) const;
  void GenerateSwappingCode(io::Printer* printer) const;
  void GenerateConstructorCode(io::Printer* printer) const;
  void GenerateMergeFromCodedStream(io::Printer* printer) const;
  void GenerateSerializeWithCachedSizes(io::Printer* printer) const;
  void GenerateSerializeWithCachedSizesToArray(io::Printer* printer) const;
  void GenerateByteSize(io::Printer* printer) const;

 private:
  void InternalGenerateTypeDependentAccessorDeclarations(
      io::Printer* printer) const;

  const FieldDescriptor* descriptor_;
  const bool dependent_field_;
  const bool dependent_getter_;
  map<string, string> variables_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(RepeatedMessageFieldGenerator);
};

}  // namespace cpp
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_CPP_MESSAGE_FIELD_H__
