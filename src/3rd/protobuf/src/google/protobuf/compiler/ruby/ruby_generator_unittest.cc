
#include <memory>

#include <google/protobuf/compiler/ruby/ruby_generator.h>
#include <google/protobuf/compiler/command_line_interface.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/io/printer.h>

#include <google/protobuf/testing/googletest.h>
#include <gtest/gtest.h>
#include <google/protobuf/testing/file.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace ruby {
namespace {

string FindRubyTestDir() {
  return TestSourceDir() + "/google/protobuf/compiler/ruby";
}

// This test is a simple golden-file test over the output of the Ruby code
// generator. When we make changes to the Ruby extension and alter the Ruby code
// generator to use those changes, we should (i) manually test the output of the
// code generator with the extension, and (ii) update the golden output above.
// Some day, we may integrate build systems between protoc and the language
// extensions to the point where we can do this test in a more automated way.

TEST(RubyGeneratorTest, GeneratorTest) {
  string ruby_tests = FindRubyTestDir();

  google::protobuf::compiler::CommandLineInterface cli;
  cli.SetInputsAreProtoPathRelative(true);

  ruby::Generator ruby_generator;
  cli.RegisterGenerator("--ruby_out", &ruby_generator, "");

  // Copy generated_code.proto to the temporary test directory.
  string test_input;
  GOOGLE_CHECK_OK(File::GetContents(
      ruby_tests + "/ruby_generated_code.proto",
      &test_input,
      true));
  GOOGLE_CHECK_OK(File::SetContents(
      TestTempDir() + "/ruby_generated_code.proto",
      test_input,
      true));

  // Invoke the proto compiler (we will be inside TestTempDir() at this point).
  string ruby_out = "--ruby_out=" + TestTempDir();
  string proto_path = "--proto_path=" + TestTempDir();
  const char* argv[] = {
    "protoc",
    ruby_out.c_str(),
    proto_path.c_str(),
    "ruby_generated_code.proto",
  };

  EXPECT_EQ(0, cli.Run(4, argv));

  // Load the generated output and compare to the expected result.
  string output;
  GOOGLE_CHECK_OK(File::GetContents(
      TestTempDir() + "/ruby_generated_code_pb.rb",
      &output,
      true));
  string expected_output;
  GOOGLE_CHECK_OK(File::GetContents(
      ruby_tests + "/ruby_generated_code_pb.rb",
      &expected_output,
      true));
  EXPECT_EQ(expected_output, output);
}

}  // namespace
}  // namespace ruby
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
