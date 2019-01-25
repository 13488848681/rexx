
#include <google/protobuf/compiler/javanano/javanano_extension.h>
#include <google/protobuf/compiler/javanano/javanano_helpers.h>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/stubs/strutil.h>
#include <google/protobuf/wire_format.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace javanano {

using internal::WireFormat;
using internal::WireFormatLite;

namespace {

const char* GetTypeConstantName(const FieldDescriptor::Type type) {
  switch (type) {
    case FieldDescriptor::TYPE_INT32   : return "TYPE_INT32"   ;
    case FieldDescriptor::TYPE_UINT32  : return "TYPE_UINT32"  ;
    case FieldDescriptor::TYPE_SINT32  : return "TYPE_SINT32"  ;
    case FieldDescriptor::TYPE_FIXED32 : return "TYPE_FIXED32" ;
    case FieldDescriptor::TYPE_SFIXED32: return "TYPE_SFIXED32";
    case FieldDescriptor::TYPE_INT64   : return "TYPE_INT64"   ;
    case FieldDescriptor::TYPE_UINT64  : return "TYPE_UINT64"  ;
    case FieldDescriptor::TYPE_SINT64  : return "TYPE_SINT64"  ;
    case FieldDescriptor::TYPE_FIXED64 : return "TYPE_FIXED64" ;
    case FieldDescriptor::TYPE_SFIXED64: return "TYPE_SFIXED64";
    case FieldDescriptor::TYPE_FLOAT   : return "TYPE_FLOAT"   ;
    case FieldDescriptor::TYPE_DOUBLE  : return "TYPE_DOUBLE"  ;
    case FieldDescriptor::TYPE_BOOL    : return "TYPE_BOOL"    ;
    case FieldDescriptor::TYPE_STRING  : return "TYPE_STRING"  ;
    case FieldDescriptor::TYPE_BYTES   : return "TYPE_BYTES"   ;
    case FieldDescriptor::TYPE_ENUM    : return "TYPE_ENUM"    ;
    case FieldDescriptor::TYPE_GROUP   : return "TYPE_GROUP"   ;
    case FieldDescriptor::TYPE_MESSAGE : return "TYPE_MESSAGE" ;

    // No default because we want the compiler to complain if any new
    // types are added.
  }

  GOOGLE_LOG(FATAL) << "Can't get here.";
  return NULL;
}

}  // namespace

void SetVariables(const FieldDescriptor* descriptor, const Params params,
                  map<string, string>* variables) {
  (*variables)["extends"] = ClassName(params, descriptor->containing_type());
  (*variables)["name"] = RenameJavaKeywords(UnderscoresToCamelCase(descriptor));
  bool repeated = descriptor->is_repeated();
  (*variables)["repeated"] = repeated ? "Repeated" : "";
  (*variables)["type"] = GetTypeConstantName(descriptor->type());
  JavaType java_type = GetJavaType(descriptor->type());
  string tag = SimpleItoa(WireFormat::MakeTag(descriptor));
  if (java_type == JAVATYPE_MESSAGE) {
    (*variables)["ext_type"] = "MessageTyped";
    string message_type = ClassName(params, descriptor->message_type());
    if (repeated) {
      message_type += "[]";
    }
    (*variables)["class"] = message_type;
    // For message typed extensions, tags_params contains a single tag
    // for both singular and repeated cases.
    (*variables)["tag_params"] = tag;
  } else {
    (*variables)["ext_type"] = "PrimitiveTyped";
    if (!repeated) {
      (*variables)["class"] = BoxedPrimitiveTypeName(java_type);
      (*variables)["tag_params"] = tag;
    } else {
      (*variables)["class"] = PrimitiveTypeName(java_type) + "[]";
      if (!descriptor->is_packable()) {
        // Non-packable: nonPackedTag == tag, packedTag == 0
        (*variables)["tag_params"] = tag + ", " + tag + ", 0";
      } else if (descriptor->options().packed()) {
        // Packable and packed: tag == packedTag
        string non_packed_tag = SimpleItoa(WireFormatLite::MakeTag(
            descriptor->number(),
            WireFormat::WireTypeForFieldType(descriptor->type())));
        (*variables)["tag_params"] = tag + ", " + non_packed_tag + ", " + tag;
      } else {
        // Packable and not packed: tag == nonPackedTag
        string packed_tag = SimpleItoa(WireFormatLite::MakeTag(
            descriptor->number(), WireFormatLite::WIRETYPE_LENGTH_DELIMITED));
        (*variables)["tag_params"] = tag + ", " + tag + ", " + packed_tag;
      }
    }
  }
}

ExtensionGenerator::
ExtensionGenerator(const FieldDescriptor* descriptor, const Params& params)
  : params_(params), descriptor_(descriptor) {
  SetVariables(descriptor, params, &variables_);
}

ExtensionGenerator::~ExtensionGenerator() {}

void ExtensionGenerator::Generate(io::Printer* printer) const {
  printer->Print("\n");
  PrintFieldComment(printer, descriptor_);
  printer->Print(variables_,
    "public static final com.google.protobuf.nano.Extension<\n"
    "    $extends$,\n"
    "    $class$> $name$ =\n"
    "        com.google.protobuf.nano.Extension.create$repeated$$ext_type$(\n"
    "            com.google.protobuf.nano.Extension.$type$,\n"
    "            $class$.class,\n"
    "            $tag_params$L);\n");
}

}  // namespace javanano
}  // namespace compiler
}  // namespace protobuf
}  // namespace google

