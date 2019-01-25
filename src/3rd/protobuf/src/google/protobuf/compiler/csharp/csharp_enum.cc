#include <sstream>

#include <google/protobuf/compiler/code_generator.h>
#include <google/protobuf/compiler/plugin.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/stubs/strutil.h>

#include <google/protobuf/compiler/csharp/csharp_doc_comment.h>
#include <google/protobuf/compiler/csharp/csharp_enum.h>
#include <google/protobuf/compiler/csharp/csharp_helpers.h>
#include <google/protobuf/compiler/csharp/csharp_options.h>

using google::protobuf::internal::scoped_ptr;

namespace google {
namespace protobuf {
namespace compiler {
namespace csharp {

EnumGenerator::EnumGenerator(const EnumDescriptor* descriptor, const Options* options) :
    SourceGeneratorBase(descriptor->file(), options),
    descriptor_(descriptor) {
}

EnumGenerator::~EnumGenerator() {
}

void EnumGenerator::Generate(io::Printer* printer) {
  WriteEnumDocComment(printer, descriptor_);
  printer->Print("$access_level$ enum $name$ {\n",
                 "access_level", class_access_level(),
                 "name", descriptor_->name());
  printer->Indent();
  std::set<string> used_names;
  for (int i = 0; i < descriptor_->value_count(); i++) {
      WriteEnumValueDocComment(printer, descriptor_->value(i));
      string original_name = descriptor_->value(i)->name();
      string name = GetEnumValueName(descriptor_->name(), descriptor_->value(i)->name());
      // Make sure we don't get any duplicate names due to prefix removal.
      while (!used_names.insert(name).second) {
        // It's possible we'll end up giving this warning multiple times, but that's better than not at all.
        GOOGLE_LOG(WARNING) << "Duplicate enum value " << name << " (originally " << original_name
          << ") in " << descriptor_->name() << "; adding underscore to distinguish";
        name += "_";
      }
      printer->Print("[pbr::OriginalName(\"$original_name$\")] $name$ = $number$,\n",
         "original_name", original_name,
         "name", name,
         "number", SimpleItoa(descriptor_->value(i)->number()));         
  }
  printer->Outdent();
  printer->Print("}\n");
  printer->Print("\n");
}

}  // namespace csharp
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
