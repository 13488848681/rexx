
#include <iostream>

#include <google/protobuf/compiler/objectivec/objectivec_extension.h>
#include <google/protobuf/compiler/objectivec/objectivec_helpers.h>
#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/stubs/strutil.h>
#include <google/protobuf/io/printer.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace objectivec {

ExtensionGenerator::ExtensionGenerator(const string& root_class_name,
                                       const FieldDescriptor* descriptor)
    : method_name_(ExtensionMethodName(descriptor)),
      root_class_and_method_name_(root_class_name + "_" + method_name_),
      descriptor_(descriptor) {
  if (descriptor->is_map()) {
    // NOTE: src/google/protobuf/compiler/plugin.cc makes use of cerr for some
    // error cases, so it seems to be ok to use as a back door for errors.
    cerr << "error: Extension is a map<>!"
         << " That used to be blocked by the compiler." << endl;
    cerr.flush();
    abort();
  }
}

ExtensionGenerator::~ExtensionGenerator() {}

void ExtensionGenerator::GenerateMembersHeader(io::Printer* printer) {
  map<string, string> vars;
  vars["method_name"] = method_name_;
  SourceLocation location;
  if (descriptor_->GetSourceLocation(&location)) {
    vars["comments"] = BuildCommentsString(location, true);
  } else {
    vars["comments"] = "";
  }
  printer->Print(vars,
                 "$comments$"
                 "+ (GPBExtensionDescriptor *)$method_name$;\n");
}

void ExtensionGenerator::GenerateStaticVariablesInitialization(
    io::Printer* printer) {
  map<string, string> vars;
  vars["root_class_and_method_name"] = root_class_and_method_name_;
  vars["extended_type"] = ClassName(descriptor_->containing_type());
  vars["number"] = SimpleItoa(descriptor_->number());

  std::vector<string> options;
  if (descriptor_->is_repeated()) options.push_back("GPBExtensionRepeated");
  if (descriptor_->is_packed()) options.push_back("GPBExtensionPacked");
  if (descriptor_->containing_type()->options().message_set_wire_format())
    options.push_back("GPBExtensionSetWireFormat");

  vars["options"] = BuildFlagsString(options);

  ObjectiveCType objc_type = GetObjectiveCType(descriptor_);
  string singular_type;
  if (objc_type == OBJECTIVECTYPE_MESSAGE) {
    vars["type"] = string("GPBStringifySymbol(") +
                   ClassName(descriptor_->message_type()) + ")";
  } else {
    vars["type"] = "NULL";
  }

  vars["default_name"] = GPBGenericValueFieldName(descriptor_);
  if (descriptor_->is_repeated()) {
    vars["default"] = "nil";
  } else {
    vars["default"] = DefaultValue(descriptor_);
  }
  string type = GetCapitalizedType(descriptor_);
  vars["extension_type"] = string("GPBDataType") + type;

  if (objc_type == OBJECTIVECTYPE_ENUM) {
    vars["enum_desc_func_name"] =
         EnumName(descriptor_->enum_type()) + "_EnumDescriptor";
  } else {
    vars["enum_desc_func_name"] = "NULL";
  }

  printer->Print(vars,
                 "{\n"
                 "  .defaultValue.$default_name$ = $default$,\n"
                 "  .singletonName = GPBStringifySymbol($root_class_and_method_name$),\n"
                 "  .extendedClass = GPBStringifySymbol($extended_type$),\n"
                 "  .messageOrGroupClassName = $type$,\n"
                 "  .enumDescriptorFunc = $enum_desc_func_name$,\n"
                 "  .fieldNumber = $number$,\n"
                 "  .dataType = $extension_type$,\n"
                 "  .options = $options$,\n"
                 "},\n");
}

void ExtensionGenerator::GenerateRegistrationSource(io::Printer* printer) {
  printer->Print(
      "[registry addExtension:$root_class_and_method_name$];\n",
      "root_class_and_method_name", root_class_and_method_name_);
}
}  // namespace objectivec
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
