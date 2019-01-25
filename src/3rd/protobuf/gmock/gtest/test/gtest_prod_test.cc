
#include "gtest/gtest.h"
#include "test/production.h"

// Tests that private members can be accessed from a TEST declared as
// a friend of the class.
TEST(PrivateCodeTest, CanAccessPrivateMembers) {
  PrivateCode a;
  EXPECT_EQ(0, a.x_);

  a.set_x(1);
  EXPECT_EQ(1, a.x_);
}

typedef testing::Test PrivateCodeFixtureTest;

// Tests that private members can be accessed from a TEST_F declared
// as a friend of the class.
TEST_F(PrivateCodeFixtureTest, CanAccessPrivateMembers) {
  PrivateCode a;
  EXPECT_EQ(0, a.x_);

  a.set_x(2);
  EXPECT_EQ(2, a.x_);
}
