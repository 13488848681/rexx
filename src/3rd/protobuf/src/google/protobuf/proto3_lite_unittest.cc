
#include <string>
#include <memory>
#ifndef _SHARED_PTR_H
#include <google/protobuf/stubs/shared_ptr.h>
#endif
#include <vector>

#include <google/protobuf/test_util.h>
#include <google/protobuf/unittest.pb.h>
#include <google/protobuf/unittest_proto3_lite.pb.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/testing/googletest.h>
#include <gtest/gtest.h>

namespace google {
using proto3_lite_unittest::TestAllTypes;

namespace protobuf {
namespace {
// We selectively set/check a few representative fields rather than all fields
// as this test is only expected to cover the basics of lite support.
void SetAllFields(TestAllTypes* m) {
  m->set_optional_int32(100);
  m->set_optional_string("asdf");
  m->set_optional_bytes("jkl;");
  m->mutable_optional_nested_message()->set_bb(42);
  m->mutable_optional_foreign_message()->set_c(43);
  m->set_optional_nested_enum(
      proto3_lite_unittest::TestAllTypes_NestedEnum_BAZ);
  m->set_optional_foreign_enum(
      proto3_lite_unittest::FOREIGN_BAZ);
  m->mutable_optional_lazy_message()->set_bb(45);
  m->add_repeated_int32(100);
  m->add_repeated_string("asdf");
  m->add_repeated_bytes("jkl;");
  m->add_repeated_nested_message()->set_bb(46);
  m->add_repeated_foreign_message()->set_c(47);
  m->add_repeated_nested_enum(
      proto3_lite_unittest::TestAllTypes_NestedEnum_BAZ);
  m->add_repeated_foreign_enum(
      proto3_lite_unittest::FOREIGN_BAZ);
  m->add_repeated_lazy_message()->set_bb(49);

  m->set_oneof_uint32(1);
  m->mutable_oneof_nested_message()->set_bb(50);
  m->set_oneof_string("test");  // only this one remains set
}

void ExpectAllFieldsSet(const TestAllTypes& m) {
  EXPECT_EQ(100, m.optional_int32());
  EXPECT_EQ("asdf", m.optional_string());
  EXPECT_EQ("jkl;", m.optional_bytes());
  EXPECT_EQ(true, m.has_optional_nested_message());
  EXPECT_EQ(42, m.optional_nested_message().bb());
  EXPECT_EQ(true, m.has_optional_foreign_message());
  EXPECT_EQ(43, m.optional_foreign_message().c());
  EXPECT_EQ(proto3_lite_unittest::TestAllTypes_NestedEnum_BAZ,
            m.optional_nested_enum());
  EXPECT_EQ(proto3_lite_unittest::FOREIGN_BAZ,
            m.optional_foreign_enum());
  EXPECT_EQ(true, m.has_optional_lazy_message());
  EXPECT_EQ(45, m.optional_lazy_message().bb());

  EXPECT_EQ(1, m.repeated_int32_size());
  EXPECT_EQ(100, m.repeated_int32(0));
  EXPECT_EQ(1, m.repeated_string_size());
  EXPECT_EQ("asdf", m.repeated_string(0));
  EXPECT_EQ(1, m.repeated_bytes_size());
  EXPECT_EQ("jkl;", m.repeated_bytes(0));
  EXPECT_EQ(1, m.repeated_nested_message_size());
  EXPECT_EQ(46, m.repeated_nested_message(0).bb());
  EXPECT_EQ(1, m.repeated_foreign_message_size());
  EXPECT_EQ(47, m.repeated_foreign_message(0).c());
  EXPECT_EQ(1, m.repeated_nested_enum_size());
  EXPECT_EQ(proto3_lite_unittest::TestAllTypes_NestedEnum_BAZ,
            m.repeated_nested_enum(0));
  EXPECT_EQ(1, m.repeated_foreign_enum_size());
  EXPECT_EQ(proto3_lite_unittest::FOREIGN_BAZ,
            m.repeated_foreign_enum(0));
  EXPECT_EQ(1, m.repeated_lazy_message_size());
  EXPECT_EQ(49, m.repeated_lazy_message(0).bb());

  EXPECT_EQ(proto3_lite_unittest::TestAllTypes::kOneofString,
            m.oneof_field_case());
  EXPECT_EQ("test", m.oneof_string());
}

// In this file we only test some basic functionalities of in proto3 and expect
// the rest is fully tested in proto2 unittests because proto3 shares most code
// with proto2.

TEST(Proto3LiteTest, Parsing) {
  TestAllTypes original;
  SetAllFields(&original);

  TestAllTypes msg;
  msg.ParseFromString(original.SerializeAsString());
  ExpectAllFieldsSet(msg);
}

TEST(Proto3LiteTest, Swap) {
  // Test Swap().
  TestAllTypes msg1;
  TestAllTypes msg2;
  msg1.set_optional_string("123");
  msg2.set_optional_string("3456");
  msg1.Swap(&msg2);
  EXPECT_EQ("3456", msg1.optional_string());
  EXPECT_EQ("123", msg2.optional_string());
  EXPECT_EQ(msg1.ByteSize(), msg2.ByteSize() + 1);
}

}  // namespace
}  // namespace protobuf
}  // namespace google
