#include <sstream>

#include <google/protobuf/compiler/code_generator.h>
#include <google/protobuf/compiler/plugin.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/io/zero_copy_stream.h>

#include <google/protobuf/compiler/csharp/csharp_source_generator_base.h>
#include <google/protobuf/compiler/csharp/csharp_helpers.h>
#include <google/protobuf/compiler/csharp/csharp_names.h>
#include <google/protobuf/compiler/csharp/csharp_options.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace csharp {

SourceGeneratorBase::SourceGeneratorBase(const FileDescriptor* descriptor,
                                         const Options *options)
    : descriptor_(descriptor), options_(options) {
}

SourceGeneratorBase::~SourceGeneratorBase() {
}

void SourceGeneratorBase::WriteGeneratedCodeAttributes(io::Printer* printer) {
  printer->Print("[global::System.Diagnostics.DebuggerNonUserCodeAttribute]\n");
}

std::string SourceGeneratorBase::class_access_level() {
  return (IsDescriptorProto(descriptor_) || this->options()->internal_access) ? "internal" : "public";
}

const Options* SourceGeneratorBase::options() {
  return this->options_;
}

}  // namespace csharp
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
