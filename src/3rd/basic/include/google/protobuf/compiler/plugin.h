
#ifndef GOOGLE_PROTOBUF_COMPILER_PLUGIN_H__
#define GOOGLE_PROTOBUF_COMPILER_PLUGIN_H__

#include <string>

#include <google/protobuf/stubs/common.h>
namespace google {
namespace protobuf {
namespace compiler {

class CodeGenerator;    // code_generator.h
class CodeGeneratorRequest;
class CodeGeneratorResponse;

// Implements main() for a protoc plugin exposing the given code generator.
LIBPROTOC_EXPORT int PluginMain(int argc, char* argv[], const CodeGenerator* generator);

// Generates code using the given code generator. Returns true if the code
// generation is successful. If the code geneartion fails, error_msg may be
// populated to describe the failure cause.
bool GenerateCode(const CodeGeneratorRequest& request,
    const CodeGenerator& generator, CodeGeneratorResponse* response,
    string* error_msg);

}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_PLUGIN_H__
