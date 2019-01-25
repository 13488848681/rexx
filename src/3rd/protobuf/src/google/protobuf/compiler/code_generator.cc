
#include <google/protobuf/compiler/code_generator.h>

#include <google/protobuf/stubs/logging.h>
#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/strutil.h>

namespace google {
namespace protobuf {
namespace compiler {

CodeGenerator::~CodeGenerator() {}
GeneratorContext::~GeneratorContext() {}

io::ZeroCopyOutputStream*
GeneratorContext::OpenForAppend(const string& filename) {
  return NULL;
}

io::ZeroCopyOutputStream* GeneratorContext::OpenForInsert(
    const string& filename, const string& insertion_point) {
  GOOGLE_LOG(FATAL) << "This GeneratorContext does not support insertion.";
  return NULL;  // make compiler happy
}

void GeneratorContext::ListParsedFiles(
    vector<const FileDescriptor*>* output) {
  GOOGLE_LOG(FATAL) << "This GeneratorContext does not support ListParsedFiles";
}

// Parses a set of comma-delimited name/value pairs.
void ParseGeneratorParameter(const string& text,
                             vector<pair<string, string> >* output) {
  vector<string> parts = Split(text, ",", true);

  for (int i = 0; i < parts.size(); i++) {
    string::size_type equals_pos = parts[i].find_first_of('=');
    pair<string, string> value;
    if (equals_pos == string::npos) {
      value.first = parts[i];
      value.second = "";
    } else {
      value.first = parts[i].substr(0, equals_pos);
      value.second = parts[i].substr(equals_pos + 1);
    }
    output->push_back(value);
  }
}

}  // namespace compiler
}  // namespace protobuf
}  // namespace google
