
#include "gtest/gtest.h"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  // An ad-hoc assertion outside of all tests.
  //
  // This serves three purposes:
  //
  // 1. It verifies that an ad-hoc assertion can be executed even if
  //    no test is defined.
  // 2. It verifies that a failed ad-hoc assertion causes the test
  //    program to fail.
  // 3. We had a bug where the XML output won't be generated if an
  //    assertion is executed before RUN_ALL_TESTS() is called, even
  //    though --gtest_output=xml is specified.  This makes sure the
  //    bug is fixed and doesn't regress.
  EXPECT_EQ(1, 2);

  // The above EXPECT_EQ() should cause RUN_ALL_TESTS() to return non-zero.
  return RUN_ALL_TESTS() ? 0 : 1;
}
