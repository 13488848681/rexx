
#include <google/protobuf/arenastring.h>

#include <string>
#include <memory>
#ifndef _SHARED_PTR_H
#include <google/protobuf/stubs/shared_ptr.h>
#endif
#include <cstdlib>

#include <google/protobuf/stubs/logging.h>
#include <google/protobuf/stubs/common.h>
#include <gtest/gtest.h>

namespace google {
using google::protobuf::internal::ArenaString;
using google::protobuf::internal::ArenaStringPtr;

namespace protobuf {


static string WrapString(const char* value) {
  return value;
}

// Test ArenaStringPtr with arena == NULL.
TEST(ArenaStringPtrTest, ArenaStringPtrOnHeap) {
  ArenaStringPtr field;
  ::std::string default_value = "default";
  field.UnsafeSetDefault(&default_value);
  EXPECT_EQ(string("default"), field.Get(&default_value));
  field.Set(&default_value, WrapString("Test short"), NULL);
  EXPECT_EQ(string("Test short"), field.Get(&default_value));
  field.Set(&default_value, WrapString("Test long long long long value"), NULL);
  EXPECT_EQ(string("Test long long long long value"), field.Get(&default_value));
  field.Set(&default_value, string(""), NULL);
  field.Destroy(&default_value, NULL);

  ArenaStringPtr field2;
  field2.UnsafeSetDefault(&default_value);
  ::std::string* mut = field2.Mutable(&default_value, NULL);
  EXPECT_EQ(mut, field2.Mutable(&default_value, NULL));
  EXPECT_EQ(mut, &field2.Get(&default_value));
  EXPECT_NE(&default_value, mut);
  EXPECT_EQ(string("default"), *mut);
  *mut = "Test long long long long value";  // ensure string allocates storage
  EXPECT_EQ(string("Test long long long long value"), field2.Get(&default_value));
  field2.Destroy(&default_value, NULL);
}

TEST(ArenaStringPtrTest, ArenaStringPtrOnArena) {
  google::protobuf::Arena arena;
  ArenaStringPtr field;
  ::std::string default_value = "default";
  field.UnsafeSetDefault(&default_value);
  EXPECT_EQ(string("default"), field.Get(&default_value));
  field.Set(&default_value, WrapString("Test short"), &arena);
  EXPECT_EQ(string("Test short"), field.Get(&default_value));
  field.Set(&default_value, WrapString("Test long long long long value"), &arena);
  EXPECT_EQ(string("Test long long long long value"),
            field.Get(&default_value));
  field.Set(&default_value, string(""), &arena);
  field.Destroy(&default_value, &arena);

  ArenaStringPtr field2;
  field2.UnsafeSetDefault(&default_value);
  ::std::string* mut = field2.Mutable(&default_value, &arena);
  EXPECT_EQ(mut, field2.Mutable(&default_value, &arena));
  EXPECT_EQ(mut, &field2.Get(&default_value));
  EXPECT_NE(&default_value, mut);
  EXPECT_EQ(string("default"), *mut);
  *mut = "Test long long long long value";  // ensure string allocates storage
  EXPECT_EQ(string("Test long long long long value"),
            field2.Get(&default_value));
  field2.Destroy(&default_value, &arena);
}

}  // namespace protobuf
}  // namespace google
