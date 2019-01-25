
#include <google/protobuf/stubs/stringprintf.h>

#include <cerrno>
#include <string>

#include <google/protobuf/testing/googletest.h>
#include <gtest/gtest.h>

namespace google {
namespace protobuf {
namespace {

TEST(StringPrintfTest, Empty) {
#if 0
  // gcc 2.95.3, gcc 4.1.0, and gcc 4.2.2 all warn about this:
  // warning: zero-length printf format string.
  // so we do not allow them in google3.
  EXPECT_EQ("", StringPrintf(""));
#endif
  EXPECT_EQ("", StringPrintf("%s", string().c_str()));
  EXPECT_EQ("", StringPrintf("%s", ""));
}

TEST(StringPrintfTest, Misc) {
// MSVC and mingw does not support $ format specifier.
#if !defined(_MSC_VER) && !defined(__MINGW32__)
  EXPECT_EQ("123hello w", StringPrintf("%3$d%2$s %1$c", 'w', "hello", 123));
#endif  // !_MSC_VER
}

TEST(StringAppendFTest, Empty) {
  string value("Hello");
  const char* empty = "";
  StringAppendF(&value, "%s", empty);
  EXPECT_EQ("Hello", value);
}

TEST(StringAppendFTest, EmptyString) {
  string value("Hello");
  StringAppendF(&value, "%s", "");
  EXPECT_EQ("Hello", value);
}

TEST(StringAppendFTest, String) {
  string value("Hello");
  StringAppendF(&value, " %s", "World");
  EXPECT_EQ("Hello World", value);
}

TEST(StringAppendFTest, Int) {
  string value("Hello");
  StringAppendF(&value, " %d", 123);
  EXPECT_EQ("Hello 123", value);
}

TEST(StringPrintfTest, Multibyte) {
  // If we are in multibyte mode and feed invalid multibyte sequence,
  // StringPrintf should return an empty string instead of running
  // out of memory while trying to determine destination buffer size.
  // see b/4194543.

  char* old_locale = setlocale(LC_CTYPE, NULL);
  // Push locale with multibyte mode
  setlocale(LC_CTYPE, "en_US.utf8");

  const char kInvalidCodePoint[] = "\375\067s";
  string value = StringPrintf("%.*s", 3, kInvalidCodePoint);

  // In some versions of glibc (e.g. eglibc-2.11.1, aka GRTEv2), snprintf
  // returns error given an invalid codepoint. Other versions
  // (e.g. eglibc-2.15, aka pre-GRTEv3) emit the codepoint verbatim.
  // We test that the output is one of the above.
  EXPECT_TRUE(value.empty() || value == kInvalidCodePoint);

  // Repeat with longer string, to make sure that the dynamically
  // allocated path in StringAppendV is handled correctly.
  int n = 2048;
  char* buf = new char[n+1];
  memset(buf, ' ', n-3);
  memcpy(buf + n - 3, kInvalidCodePoint, 4);
  value =  StringPrintf("%.*s", n, buf);
  // See GRTEv2 vs. GRTEv3 comment above.
  EXPECT_TRUE(value.empty() || value == buf);
  delete[] buf;

  setlocale(LC_CTYPE, old_locale);
}

TEST(StringPrintfTest, NoMultibyte) {
  // No multibyte handling, but the string contains funny chars.
  char* old_locale = setlocale(LC_CTYPE, NULL);
  setlocale(LC_CTYPE, "POSIX");
  string value = StringPrintf("%.*s", 3, "\375\067s");
  setlocale(LC_CTYPE, old_locale);
  EXPECT_EQ("\375\067s", value);
}

TEST(StringPrintfTest, DontOverwriteErrno) {
  // Check that errno isn't overwritten unless we're printing
  // something significantly larger than what people are normally
  // printing in their badly written PLOG() statements.
  errno = ECHILD;
  string value = StringPrintf("Hello, %s!", "World");
  EXPECT_EQ(ECHILD, errno);
}

TEST(StringPrintfTest, LargeBuf) {
  // Check that the large buffer is handled correctly.
  int n = 2048;
  char* buf = new char[n+1];
  memset(buf, ' ', n);
  buf[n] = 0;
  string value = StringPrintf("%s", buf);
  EXPECT_EQ(buf, value);
  delete[] buf;
}

}  // anonymous namespace
}  // namespace protobuf
}  // namespace google
