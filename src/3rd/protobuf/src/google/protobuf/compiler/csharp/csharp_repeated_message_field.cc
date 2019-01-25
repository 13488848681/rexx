#include <sstream>

#include <google/protobuf/compiler/code_generator.h>
#include <google/protobuf/compiler/plugin.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/io/zero_copy_stream.h>

#include <google/protobuf/compiler/csharp/csharp_doc_comment.h>
#include <google/protobuf/compiler/csharp/csharp_helpers.h>
#include <google/protobuf/compiler/csharp/csharp_repeated_message_field.h>
#include <google/protobuf/compiler/csharp/csharp_message_field.h>
#include <google/protobuf/compiler/csharp/csharp_wrapper_field.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace csharp {

RepeatedMessageFieldGenerator::RepeatedMessageFieldGenerator(
    const FieldDescriptor* descriptor, int fieldOrdinal, const Options *options)
    : FieldGeneratorBase(descriptor, fieldOrdinal, options) {
}

RepeatedMessageFieldGenerator::~RepeatedMessageFieldGenerator() {

}

void RepeatedMessageFieldGenerator::GenerateMembers(io::Printer* printer) {
  printer->Print(
    variables_,
    "private static readonly pb::FieldCodec<$type_name$> _repeated_$name$_codec\n"
    "    = ");
  // Don't want to duplicate the codec code here... maybe we should have a
  // "create single field generator for this repeated field"
  // function, but it doesn't seem worth it for just this.
  if (IsWrapperType(descriptor_)) {
    scoped_ptr<FieldGeneratorBase> single_generator(
      new WrapperFieldGenerator(descriptor_, fieldOrdinal_, this->options()));
    single_generator->GenerateCodecCode(printer);
  } else {
    scoped_ptr<FieldGeneratorBase> single_generator(
      new MessageFieldGenerator(descriptor_, fieldOrdinal_, this->options()));
    single_generator->GenerateCodecCode(printer);
  }
  printer->Print(";\n");
  printer->Print(
    variables_,
    "private readonly pbc::RepeatedField<$type_name$> $name$_ = new pbc::RepeatedField<$type_name$>();\n");
  WritePropertyDocComment(printer, descriptor_);
  AddPublicMemberAttributes(printer);
  printer->Print(
    variables_,
    "$access_level$ pbc::RepeatedField<$type_name$> $property_name$ {\n"
    "  get { return $name$_; }\n"
    "}\n");
}

void RepeatedMessageFieldGenerator::GenerateMergingCode(io::Printer* printer) {
  printer->Print(
    variables_,
    "$name$_.Add(other.$name$_);\n");
}

void RepeatedMessageFieldGenerator::GenerateParsingCode(io::Printer* printer) {
  printer->Print(
    variables_,
    "$name$_.AddEntriesFrom(input, _repeated_$name$_codec);\n");
}

void RepeatedMessageFieldGenerator::GenerateSerializationCode(io::Printer* printer) {
  printer->Print(
    variables_,
    "$name$_.WriteTo(output, _repeated_$name$_codec);\n");
}

void RepeatedMessageFieldGenerator::GenerateSerializedSizeCode(io::Printer* printer) {
  printer->Print(
    variables_,
    "size += $name$_.CalculateSize(_repeated_$name$_codec);\n");
}

void RepeatedMessageFieldGenerator::WriteHash(io::Printer* printer) {
  printer->Print(
    variables_,
    "hash ^= $name$_.GetHashCode();\n");
}

void RepeatedMessageFieldGenerator::WriteEquals(io::Printer* printer) {
  printer->Print(
    variables_,
    "if(!$name$_.Equals(other.$name$_)) return false;\n");
}

void RepeatedMessageFieldGenerator::WriteToString(io::Printer* printer) {
  variables_["field_name"] = GetFieldName(descriptor_);
  printer->Print(
    variables_,
    "PrintField(\"$field_name$\", $name$_, writer);\n");
}

void RepeatedMessageFieldGenerator::GenerateCloningCode(io::Printer* printer) {
  printer->Print(variables_,
    "$name$_ = other.$name$_.Clone();\n");
}

void RepeatedMessageFieldGenerator::GenerateFreezingCode(io::Printer* printer) {
}

}  // namespace csharp
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
