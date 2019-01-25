#include <google/protobuf/compiler/java/java_doc_comment.h>

#include <gtest/gtest.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace java {
namespace {

TEST(JavaDocCommentTest, Escaping) {
  EXPECT_EQ("foo /&#42; bar *&#47; baz", EscapeJavadoc("foo /* bar */ baz"));
  EXPECT_EQ("foo /&#42;&#47; baz", EscapeJavadoc("foo /*/ baz"));
  EXPECT_EQ("{&#64;foo}", EscapeJavadoc("{@foo}"));
  EXPECT_EQ("&lt;i&gt;&amp;&lt;/i&gt;", EscapeJavadoc("<i>&</i>"));
  EXPECT_EQ("foo&#92;u1234bar", EscapeJavadoc("foo\\u1234bar"));
  EXPECT_EQ("&#64;deprecated", EscapeJavadoc("@deprecated"));
}

// TODO(kenton):  It's hard to write a robust test of the doc comments -- we
//   can only really compare the output against a golden value, which is a
//   fairly tedious and fragile testing strategy.  If we want to go that route,
//   it probably makes sense to bite the bullet and write a test that compares
//   the whole generated output for unittest.proto against a golden value, with
//   a very simple script that can be run to regenerate it with the latest code.
//   This would mean that updates to the golden file would have to be included
//   in any change to the code generator, which would actually be fairly useful
//   as it allows the reviewer to see clearly how the generated code is
//   changing.

}  // namespace
}  // namespace java
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
