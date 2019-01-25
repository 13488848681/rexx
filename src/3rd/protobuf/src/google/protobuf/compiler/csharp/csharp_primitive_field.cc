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
#include <google/protobuf/compiler/csharp/csharp_options.h>
#include <google/protobuf/compiler/csharp/csharp_primitive_field.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace csharp {

PrimitiveFieldGenerator::PrimitiveFieldGenerator(
    const FieldDescriptor* descriptor, int fieldOrdinal, const Options *options)
    : FieldGeneratorBase(descriptor, fieldOrdinal, options) {
  // TODO(jonskeet): Make this cleaner...
  is_value_type = descriptor->type() != FieldDescriptor::TYPE_STRING
      && descriptor->type() != FieldDescriptor::TYPE_BYTES;
  if (!is_value_type) {
    variables_["has_property_check"] = variables_["property_name"] + ".Length != 0";
    variables_["other_has_property_check"] = "other." + variables_["property_name"] + ".Length != 0";
  }
}

PrimitiveFieldGenerator::~PrimitiveFieldGenerator() {
}

void PrimitiveFieldGenerator::GenerateMembers(io::Printer* printer) {
  // TODO(jonskeet): Work out whether we want to prevent the fields from ever being
  // null, or whether we just handle it, in the cases of bytes and string.
  // (Basically, should null-handling code be in the getter or the setter?)
  printer->Print(
    variables_,
    "private $type_name$ $name_def_message$;\n");
  WritePropertyDocComment(printer, descriptor_);
  AddPublicMemberAttributes(printer);
  printer->Print(
    variables_,
    "$access_level$ $type_name$ $property_name$ {\n"
    "  get { return $name$_; }\n"
    "  set {\n");
  if (is_value_type) {
    printer->Print(
      variables_,
      "    $name$_ = value;\n");
  } else {
    printer->Print(
      variables_,
      "    $name$_ = pb::ProtoPreconditions.CheckNotNull(value, \"value\");\n");
  }
  printer->Print(
    "  }\n"
    "}\n");
}

void PrimitiveFieldGenerator::GenerateMergingCode(io::Printer* printer) {
  printer->Print(
    variables_,
    "if ($other_has_property_check$) {\n"
    "  $property_name$ = other.$property_name$;\n"
    "}\n");
}

void PrimitiveFieldGenerator::GenerateParsingCode(io::Printer* printer) {
  // Note: invoke the property setter rather than writing straight to the field,
  // so that we can normalize "null to empty" for strings and bytes.
  printer->Print(
    variables_,
    "$property_name$ = input.Read$capitalized_type_name$();\n");
}

void PrimitiveFieldGenerator::GenerateSerializationCode(io::Printer* printer) {
  printer->Print(
    variables_,
    "if ($has_property_check$) {\n"
    "  output.WriteRawTag($tag_bytes$);\n"
    "  output.Write$capitalized_type_name$($property_name$);\n"
    "}\n");
}

void PrimitiveFieldGenerator::GenerateSerializedSizeCode(io::Printer* printer) {
  printer->Print(
    variables_,
    "if ($has_property_check$) {\n");
  printer->Indent();
  int fixedSize = GetFixedSize(descriptor_->type());
  if (fixedSize == -1) {
    printer->Print(
      variables_,
      "size += $tag_size$ + pb::CodedOutputStream.Compute$capitalized_type_name$Size($property_name$);\n");
  } else {
    printer->Print(
      "size += $tag_size$ + $fixed_size$;\n",
      "fixed_size", SimpleItoa(fixedSize),
      "tag_size", variables_["tag_size"]);
  }
  printer->Outdent();
  printer->Print("}\n");
}

void PrimitiveFieldGenerator::WriteHash(io::Printer* printer) {
  printer->Print(
    variables_,
    "if ($has_property_check$) hash ^= $property_name$.GetHashCode();\n");
}
void PrimitiveFieldGenerator::WriteEquals(io::Printer* printer) {
  printer->Print(
    variables_,
    "if ($property_name$ != other.$property_name$) return false;\n");
}
void PrimitiveFieldGenerator::WriteToString(io::Printer* printer) {
  printer->Print(
    variables_,
    "PrintField(\"$descriptor_name$\", $has_property_check$, $property_name$, writer);\n");
}

void PrimitiveFieldGenerator::GenerateCloningCode(io::Printer* printer) {
  printer->Print(variables_,
    "$name$_ = other.$name$_;\n");
}

void PrimitiveFieldGenerator::GenerateCodecCode(io::Printer* printer) {
  printer->Print(
    variables_,
    "pb::FieldCodec.For$capitalized_type_name$($tag$)");
}

PrimitiveOneofFieldGenerator::PrimitiveOneofFieldGenerator(
    const FieldDescriptor* descriptor, int fieldOrdinal, const Options *options)
    : PrimitiveFieldGenerator(descriptor, fieldOrdinal, options) {
  SetCommonOneofFieldVariables(&variables_);
}

PrimitiveOneofFieldGenerator::~PrimitiveOneofFieldGenerator() {
}

void PrimitiveOneofFieldGenerator::GenerateMembers(io::Printer* printer) {
  WritePropertyDocComment(printer, descriptor_);
  AddPublicMemberAttributes(printer);
  printer->Print(
    variables_,
    "$access_level$ $type_name$ $property_name$ {\n"
    "  get { return $has_property_check$ ? ($type_name$) $oneof_name$_ : $default_value$; }\n"
    "  set {\n");
    if (is_value_type) {
      printer->Print(
        variables_,
        "    $oneof_name$_ = value;\n");
    } else {
      printer->Print(
        variables_,
        "    $oneof_name$_ = pb::ProtoPreconditions.CheckNotNull(value, \"value\");\n");
    }
    printer->Print(
      variables_,
      "    $oneof_name$Case_ = $oneof_property_name$OneofCase.$property_name$;\n"
      "  }\n"
      "}\n");
}

void PrimitiveOneofFieldGenerator::WriteToString(io::Printer* printer) {
  printer->Print(variables_,
    "PrintField(\"$descriptor_name$\", $has_property_check$, $oneof_name$_, writer);\n");
}

void PrimitiveOneofFieldGenerator::GenerateParsingCode(io::Printer* printer) {
    printer->Print(
      variables_,
      "$property_name$ = input.Read$capitalized_type_name$();\n");
}

void PrimitiveOneofFieldGenerator::GenerateCloningCode(io::Printer* printer) {
  printer->Print(variables_,
    "$property_name$ = other.$property_name$;\n");
}

}  // namespace csharp
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
