#include <sstream>

#include <google/protobuf/compiler/code_generator.h>
#include <google/protobuf/compiler/plugin.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/wire_format.h>

#include <google/protobuf/compiler/csharp/csharp_doc_comment.h>
#include <google/protobuf/compiler/csharp/csharp_helpers.h>
#include <google/protobuf/compiler/csharp/csharp_repeated_primitive_field.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace csharp {

RepeatedPrimitiveFieldGenerator::RepeatedPrimitiveFieldGenerator(
    const FieldDescriptor* descriptor, int fieldOrdinal, const Options *options)
    : FieldGeneratorBase(descriptor, fieldOrdinal, options) {
}

RepeatedPrimitiveFieldGenerator::~RepeatedPrimitiveFieldGenerator() {

}

void RepeatedPrimitiveFieldGenerator::GenerateMembers(io::Printer* printer) {
  printer->Print(
    variables_,
    "private static readonly pb::FieldCodec<$type_name$> _repeated_$name$_codec\n"
    "    = pb::FieldCodec.For$capitalized_type_name$($tag$);\n");
  printer->Print(variables_,
    "private readonly pbc::RepeatedField<$type_name$> $name$_ = new pbc::RepeatedField<$type_name$>();\n");
  WritePropertyDocComment(printer, descriptor_);
  AddPublicMemberAttributes(printer);
  printer->Print(
    variables_,
    "$access_level$ pbc::RepeatedField<$type_name$> $property_name$ {\n"
    "  get { return $name$_; }\n"
    "}\n");
}

void RepeatedPrimitiveFieldGenerator::GenerateMergingCode(io::Printer* printer) {
  printer->Print(
    variables_,
    "$name$_.Add(other.$name$_);\n");
}

void RepeatedPrimitiveFieldGenerator::GenerateParsingCode(io::Printer* printer) {
  printer->Print(
    variables_,
    "$name$_.AddEntriesFrom(input, _repeated_$name$_codec);\n");
}

void RepeatedPrimitiveFieldGenerator::GenerateSerializationCode(io::Printer* printer) {
  printer->Print(
    variables_,
    "$name$_.WriteTo(output, _repeated_$name$_codec);\n");
}

void RepeatedPrimitiveFieldGenerator::GenerateSerializedSizeCode(io::Printer* printer) {
  printer->Print(
    variables_,
    "size += $name$_.CalculateSize(_repeated_$name$_codec);\n");
}

void RepeatedPrimitiveFieldGenerator::WriteHash(io::Printer* printer) {
  printer->Print(
    variables_,
    "hash ^= $name$_.GetHashCode();\n");
}
void RepeatedPrimitiveFieldGenerator::WriteEquals(io::Printer* printer) {
  printer->Print(
    variables_,
    "if(!$name$_.Equals(other.$name$_)) return false;\n");
}
void RepeatedPrimitiveFieldGenerator::WriteToString(io::Printer* printer) {
  printer->Print(variables_,
    "PrintField(\"$descriptor_name$\", $name$_, writer);\n");
}

void RepeatedPrimitiveFieldGenerator::GenerateCloningCode(io::Printer* printer) {
  printer->Print(variables_,
    "$name$_ = other.$name$_.Clone();\n");
}

void RepeatedPrimitiveFieldGenerator::GenerateFreezingCode(io::Printer* printer) {
}

}  // namespace csharp
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
