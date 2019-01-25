#include <map>

#include <google/protobuf/compiler/cpp/cpp_generator.h>
#include <google/protobuf/compiler/importer.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/stubs/map_util.h>
#include <google/protobuf/stubs/stl_util.h>
#include <google/protobuf/stubs/strutil.h>
#include <google/protobuf/stubs/substitute.h>

#include <google/protobuf/testing/file.h>
#include <google/protobuf/testing/file.h>
#include <google/protobuf/testing/googletest.h>
#include <gtest/gtest.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace cpp {

namespace {

class MockErrorCollector : public MultiFileErrorCollector {
 public:
  MockErrorCollector() {}
  ~MockErrorCollector() {}

  string text_;

  // implements ErrorCollector ---------------------------------------
  void AddError(const string& filename, int line, int column,
                const string& message) {
    strings::SubstituteAndAppend(&text_, "$0:$1:$2: $3\n",
                                 filename, line, column, message);
  }
};

class MockGeneratorContext : public GeneratorContext {
 public:
  MockGeneratorContext() {}
  ~MockGeneratorContext() {
    STLDeleteValues(&files_);
  }

  void ExpectFileMatches(const string& virtual_filename,
                         const string& physical_filename) {
    string* expected_contents = FindPtrOrNull(files_, virtual_filename);
    ASSERT_TRUE(expected_contents != NULL)
      << "Generator failed to generate file: " << virtual_filename;

    string actual_contents;
    GOOGLE_CHECK_OK(
        File::GetContents(TestSourceDir() + "/" + physical_filename,
                          &actual_contents, true));
    EXPECT_TRUE(actual_contents == *expected_contents)
      << physical_filename << " needs to be regenerated.  Please run "
         "google/protobuf/compiler/release_compiler.sh and "
         "generate_descriptor_proto.sh. Then add this file "
         "to your CL.";
  }

  // implements GeneratorContext --------------------------------------

  virtual io::ZeroCopyOutputStream* Open(const string& filename) {
    string** map_slot = &files_[filename];
    delete *map_slot;
    *map_slot = new string;

    return new io::StringOutputStream(*map_slot);
  }

 private:
  map<string, string*> files_;
};

TEST(BootstrapTest, GeneratedDescriptorMatches) {
  MockErrorCollector error_collector;
  DiskSourceTree source_tree;
  source_tree.MapPath("", TestSourceDir());
  Importer importer(&source_tree, &error_collector);
  const FileDescriptor* proto_file =
    importer.Import("google/protobuf/descriptor.proto");
  const FileDescriptor* plugin_proto_file =
    importer.Import("google/protobuf/compiler/plugin.proto");
  EXPECT_EQ("", error_collector.text_);
  ASSERT_TRUE(proto_file != NULL);
  ASSERT_TRUE(plugin_proto_file != NULL);

  CppGenerator generator;
  MockGeneratorContext context;
  string error;
  string parameter = "dllexport_decl=LIBPROTOBUF_EXPORT";
  ASSERT_TRUE(generator.Generate(proto_file, parameter,
                                 &context, &error));
  parameter = "dllexport_decl=LIBPROTOC_EXPORT";
  ASSERT_TRUE(generator.Generate(plugin_proto_file, parameter,
                                 &context, &error));

  context.ExpectFileMatches("google/protobuf/descriptor.pb.h",
                            "google/protobuf/descriptor.pb.h");
  context.ExpectFileMatches("google/protobuf/descriptor.pb.cc",
                            "google/protobuf/descriptor.pb.cc");
  context.ExpectFileMatches("google/protobuf/compiler/plugin.pb.h",
                            "google/protobuf/compiler/plugin.pb.h");
  context.ExpectFileMatches("google/protobuf/compiler/plugin.pb.cc",
                            "google/protobuf/compiler/plugin.pb.cc");
}

}  // namespace

}  // namespace cpp
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
