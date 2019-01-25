
#include <google/protobuf/stubs/status.h>

#include <stdio.h>

#include <google/protobuf/testing/googletest.h>
#include <gtest/gtest.h>

namespace google {
namespace protobuf {
namespace {
TEST(Status, Empty) {
  util::Status status;
  EXPECT_EQ(util::error::OK, util::Status::OK.error_code());
  EXPECT_EQ("OK", util::Status::OK.ToString());
}

TEST(Status, GenericCodes) {
  EXPECT_EQ(util::error::OK, util::Status::OK.error_code());
  EXPECT_EQ(util::error::CANCELLED, util::Status::CANCELLED.error_code());
  EXPECT_EQ(util::error::UNKNOWN, util::Status::UNKNOWN.error_code());
}

TEST(Status, ConstructorZero) {
  util::Status status(util::error::OK, "msg");
  EXPECT_TRUE(status.ok());
  EXPECT_EQ("OK", status.ToString());
}

TEST(Status, CheckOK) {
  util::Status status;
  GOOGLE_CHECK_OK(status);
  GOOGLE_CHECK_OK(status) << "Failed";
  GOOGLE_DCHECK_OK(status) << "Failed";
}

TEST(Status, ErrorMessage) {
  util::Status status(util::error::INVALID_ARGUMENT, "");
  EXPECT_FALSE(status.ok());
  EXPECT_EQ("", status.error_message().ToString());
  EXPECT_EQ("INVALID_ARGUMENT", status.ToString());
  status = util::Status(util::error::INVALID_ARGUMENT, "msg");
  EXPECT_FALSE(status.ok());
  EXPECT_EQ("msg", status.error_message().ToString());
  EXPECT_EQ("INVALID_ARGUMENT:msg", status.ToString());
  status = util::Status(util::error::OK, "msg");
  EXPECT_TRUE(status.ok());
  EXPECT_EQ("", status.error_message().ToString());
  EXPECT_EQ("OK", status.ToString());
}

TEST(Status, Copy) {
  util::Status a(util::error::UNKNOWN, "message");
  util::Status b(a);
  ASSERT_EQ(a.ToString(), b.ToString());
}

TEST(Status, Assign) {
  util::Status a(util::error::UNKNOWN, "message");
  util::Status b;
  b = a;
  ASSERT_EQ(a.ToString(), b.ToString());
}

TEST(Status, AssignEmpty) {
  util::Status a(util::error::UNKNOWN, "message");
  util::Status b;
  a = b;
  ASSERT_EQ(string("OK"), a.ToString());
  ASSERT_TRUE(b.ok());
  ASSERT_TRUE(a.ok());
}

TEST(Status, EqualsOK) {
  ASSERT_EQ(util::Status::OK, util::Status());
}

TEST(Status, EqualsSame) {
  const util::Status a = util::Status(util::error::CANCELLED, "message");
  const util::Status b = util::Status(util::error::CANCELLED, "message");
  ASSERT_EQ(a, b);
}

TEST(Status, EqualsCopy) {
  const util::Status a = util::Status(util::error::CANCELLED, "message");
  const util::Status b = a;
  ASSERT_EQ(a, b);
}

TEST(Status, EqualsDifferentCode) {
  const util::Status a = util::Status(util::error::CANCELLED, "message");
  const util::Status b = util::Status(util::error::UNKNOWN, "message");
  ASSERT_NE(a, b);
}

TEST(Status, EqualsDifferentMessage) {
  const util::Status a = util::Status(util::error::CANCELLED, "message");
  const util::Status b = util::Status(util::error::CANCELLED, "another");
  ASSERT_NE(a, b);
}
}  // namespace
}  // namespace protobuf
}  // namespace google
