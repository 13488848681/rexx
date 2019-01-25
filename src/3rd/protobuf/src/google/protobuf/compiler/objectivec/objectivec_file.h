
#ifndef GOOGLE_PROTOBUF_COMPILER_OBJECTIVEC_FILE_H__
#define GOOGLE_PROTOBUF_COMPILER_OBJECTIVEC_FILE_H__

#include <string>
#include <set>
#include <vector>
#include <google/protobuf/compiler/objectivec/objectivec_helpers.h>
#include <google/protobuf/stubs/common.h>

namespace google {
namespace protobuf {
class FileDescriptor;  // descriptor.h
namespace io {
class Printer;  // printer.h
}
}

namespace protobuf {
namespace compiler {
namespace objectivec {

class EnumGenerator;
class ExtensionGenerator;
class MessageGenerator;

class FileGenerator {
 public:
  FileGenerator(const FileDescriptor* file, const Options& options);
  ~FileGenerator();

  void GenerateSource(io::Printer* printer);
  void GenerateHeader(io::Printer* printer);

  const string& RootClassName() const { return root_class_name_; }
  const string Path() const { return FilePath(file_); }
  const FileDescriptor* Descriptor() const { return file_; }

  bool IsPublicDependency() const { return is_public_dep_; }

 protected:
  void SetIsPublicDependency(bool is_public_dep) {
    is_public_dep_ = is_public_dep;
  }

 private:
  const FileDescriptor* file_;
  string root_class_name_;

  // Access this field through the DependencyGenerators accessor call below.
  // Do not reference it directly.
  vector<FileGenerator*> dependency_generators_;

  vector<EnumGenerator*> enum_generators_;
  vector<MessageGenerator*> message_generators_;
  vector<ExtensionGenerator*> extension_generators_;
  bool is_public_dep_;

  const Options options_;

  const vector<FileGenerator*>& DependencyGenerators();
  void PrintFileRuntimePreamble(
      io::Printer* printer, const string& header_to_import) const;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(FileGenerator);
};

}  // namespace objectivec
}  // namespace compiler
}  // namespace protobuf
}  // namespace google

#endif  // GOOGLE_PROTOBUF_COMPILER_OBJECTIVEC_FILE_H__
