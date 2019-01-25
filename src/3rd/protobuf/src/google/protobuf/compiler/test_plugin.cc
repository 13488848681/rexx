
#include <string>
#include <stdlib.h>
#include <google/protobuf/compiler/plugin.h>
#include <google/protobuf/compiler/mock_code_generator.h>
#include <google/protobuf/stubs/strutil.h>

int main(int argc, char* argv[]) {
#ifdef _MSC_VER
  // Don't print a silly message or stick a modal dialog box in my face,
  // please.
  _set_abort_behavior(0, ~0);
#endif  // !_MSC_VER

  google::protobuf::compiler::MockCodeGenerator generator("test_plugin");
  return google::protobuf::compiler::PluginMain(argc, argv, &generator);
}
