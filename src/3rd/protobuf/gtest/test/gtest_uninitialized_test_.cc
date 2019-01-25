#include "gtest/gtest.h"

TEST(DummyTest, Dummy) {
  // This test doesn't verify anything.  We just need it to create a
  // realistic stage for testing the behavior of Google Test when
  // RUN_ALL_TESTS() is called without testing::InitGoogleTest() being
  // called first.
}

int main() {
  return RUN_ALL_TESTS();
}
