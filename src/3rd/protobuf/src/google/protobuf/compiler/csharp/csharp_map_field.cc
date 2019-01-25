#include <sstream>

#include <google/protobuf/compiler/code_generator.h>
#include <google/protobuf/compiler/plugin.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/stubs/strutil.h>

#include <google/protobuf/compiler/csharp/csharp_doc_comment.h>
#include <google/protobuf/compiler/csharp/csharp_helpers.h>
#include <google/protobuf/compiler/csharp/csharp_map_field.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace csharp {

MapFieldGenerator::MapFieldGenerator(const FieldDescriptor* descriptor,
                                     int fieldOrdinal,
                                     const Options* options)
    : FieldGeneratorBase(descriptor, fieldOrdinal, options) {
}

MapFieldGenerator::~MapFieldGenerator() {
}

void MapFieldGenerator::GenerateMembers(io::Printer* printer) {   
  const FieldDescriptor* key_descriptor =
      descriptor_->message_type()->FindFieldByName("key");
  const FieldDescriptor* value_descriptor =
      descriptor_->message_type()->FindFieldByName("value");
  variables_["key_type_name"] = type_name(key_descriptor);
  variables_["value_type_name"] = type_name(value_descriptor);
  scoped_ptr<FieldGeneratorBase> key_generator(
      CreateFieldGenerator(key_descriptor, 1, this->options()));
  scoped_ptr<FieldGeneratorBase> value_generator(
      CreateFieldGenerator(value_descriptor, 2, this->options()));

  printer->Print(
    variables_,
    "private static readonly pbc::MapField<$key_type_name$, $value_type_name$>.Codec _map_$name$_codec\n"
    "    = new pbc::MapField<$key_type_name$, $value_type_name$>.Codec(");
  key_generator->GenerateCodecCode(printer);
  printer->Print(", ");
  value_generator->GenerateCodecCode(printer);
  printer->Print(
    variables_,
    ", $tag$);\n"
    "private readonly pbc::MapField<$key_type_name$, $value_type_name$> $name$_ = new pbc::MapField<$key_type_name$, $value_type_name$>();\n");
  WritePropertyDocComment(printer, descriptor_);
  AddPublicMemberAttributes(printer);
  printer->Print(
    variables_,
    "$access_level$ pbc::MapField<$key_type_name$, $value_type_name$> $property_name$ {\n"
    "  get { return $name$_; }\n"
    "}\n");
}

void MapFieldGenerator::GenerateMergingCode(io::Printer* printer) {
  printer->Print(
      variables_,
      "$name$_.Add(other.$name$_);\n");
}

void MapFieldGenerator::GenerateParsingCode(io::Printer* printer) {
  printer->Print(
    variables_,
    "$name$_.AddEntriesFrom(input, _map_$name$_codec);\n");
}

void MapFieldGenerator::GenerateSerializationCode(io::Printer* printer) {
  printer->Print(
    variables_,
    "$name$_.WriteTo(output, _map_$name$_codec);\n");
}

void MapFieldGenerator::GenerateSerializedSizeCode(io::Printer* printer) {
  printer->Print(
    variables_,
    "size += $name$_.CalculateSize(_map_$name$_codec);\n");
}

void MapFieldGenerator::WriteHash(io::Printer* printer) {
  printer->Print(
    variables_,
    "hash ^= $property_name$.GetHashCode();\n");
}
void MapFieldGenerator::WriteEquals(io::Printer* printer) {
  printer->Print(
    variables_,
    "if (!$property_name$.Equals(other.$property_name$)) return false;\n");
}

void MapFieldGenerator::WriteToString(io::Printer* printer) {
    // TODO: If we ever actually use ToString, we'll need to impleme this...
}

void MapFieldGenerator::GenerateCloningCode(io::Printer* printer) {
  printer->Print(variables_,
    "$name$_ = other.$name$_.Clone();\n");
}

void MapFieldGenerator::GenerateFreezingCode(io::Printer* printer) {
}

}  // namespace csharp
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
