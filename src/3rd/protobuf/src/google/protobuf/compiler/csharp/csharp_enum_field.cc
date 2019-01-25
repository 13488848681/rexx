#include <sstream>

#include <google/protobuf/compiler/code_generator.h>
#include <google/protobuf/compiler/plugin.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/io/zero_copy_stream.h>

#include <google/protobuf/compiler/csharp/csharp_helpers.h>
#include <google/protobuf/compiler/csharp/csharp_options.h>
#include <google/protobuf/compiler/csharp/csharp_enum_field.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace csharp {

EnumFieldGenerator::EnumFieldGenerator(const FieldDescriptor* descriptor,
                                       int fieldOrdinal, const Options *options)
    : PrimitiveFieldGenerator(descriptor, fieldOrdinal, options) {
}

EnumFieldGenerator::~EnumFieldGenerator() {
}

void EnumFieldGenerator::GenerateParsingCode(io::Printer* printer) {
  printer->Print(variables_,
    "$name$_ = ($type_name$) input.ReadEnum();\n");
}

void EnumFieldGenerator::GenerateSerializationCode(io::Printer* printer) {
  printer->Print(variables_,
    "if ($has_property_check$) {\n"
    "  output.WriteRawTag($tag_bytes$);\n"
    "  output.WriteEnum((int) $property_name$);\n"
    "}\n");
}

void EnumFieldGenerator::GenerateSerializedSizeCode(io::Printer* printer) {
  printer->Print(
    variables_,
    "if ($has_property_check$) {\n"
      "  size += $tag_size$ + pb::CodedOutputStream.ComputeEnumSize((int) $property_name$);\n"
    "}\n");
}

void EnumFieldGenerator::GenerateCodecCode(io::Printer* printer) {
    printer->Print(
        variables_,
        "pb::FieldCodec.ForEnum($tag$, x => (int) x, x => ($type_name$) x)");
}

EnumOneofFieldGenerator::EnumOneofFieldGenerator(
    const FieldDescriptor* descriptor, int fieldOrdinal, const Options *options)
  : PrimitiveOneofFieldGenerator(descriptor, fieldOrdinal, options) {
}

EnumOneofFieldGenerator::~EnumOneofFieldGenerator() {
}

void EnumOneofFieldGenerator::GenerateParsingCode(io::Printer* printer) {
  // TODO(jonskeet): What about if we read the default value?
  printer->Print(
    variables_,
    "$oneof_name$_ = input.ReadEnum();\n"
    "$oneof_name$Case_ = $oneof_property_name$OneofCase.$property_name$;\n");
}

void EnumOneofFieldGenerator::GenerateSerializationCode(io::Printer* printer) {
  printer->Print(
    variables_,
    "if ($has_property_check$) {\n"
    "  output.WriteRawTag($tag_bytes$);\n"
    "  output.WriteEnum((int) $property_name$);\n"
    "}\n");
}

void EnumOneofFieldGenerator::GenerateSerializedSizeCode(io::Printer* printer) {
  printer->Print(
    variables_,
    "if ($has_property_check$) {\n"
    "  size += $tag_size$ + pb::CodedOutputStream.ComputeEnumSize((int) $property_name$);\n"
    "}\n");
}

}  // namespace csharp
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
