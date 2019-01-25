
#include <google/protobuf/unittest_well_known_types.pb.h>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/testing/googletest.h>
#include <gtest/gtest.h>
#include <google/protobuf/stubs/stl_util.h>

namespace google {
namespace protobuf {
namespace {

// This test only checks whether well-known types are included in protobuf
// runtime library. The test passes if it compiles.
TEST(WellKnownTypesTest, AllKnownTypesAreIncluded) {
  protobuf_unittest::TestWellKnownTypes message;
  EXPECT_EQ(0, message.any_field().ByteSize());
  EXPECT_EQ(0, message.api_field().ByteSize());
  EXPECT_EQ(0, message.duration_field().ByteSize());
  EXPECT_EQ(0, message.empty_field().ByteSize());
  EXPECT_EQ(0, message.field_mask_field().ByteSize());
  EXPECT_EQ(0, message.source_context_field().ByteSize());
  EXPECT_EQ(0, message.struct_field().ByteSize());
  EXPECT_EQ(0, message.timestamp_field().ByteSize());
  EXPECT_EQ(0, message.type_field().ByteSize());
  EXPECT_EQ(0, message.int32_field().ByteSize());
}

}  // namespace

}  // namespace protobuf
}  // namespace google
