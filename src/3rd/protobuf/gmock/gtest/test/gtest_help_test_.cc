
#include "gtest/gtest.h"

// When a help flag is specified, this program should skip the tests
// and exit with 0; otherwise the following test will be executed,
// causing this program to exit with a non-zero code.
TEST(HelpFlagTest, ShouldNotBeRun) {
  ASSERT_TRUE(false) << "Tests shouldn't be run when --help is specified.";
}

#if GTEST_HAS_DEATH_TEST
TEST(DeathTest, UsedByPythonScriptToDetectSupportForDeathTestsInThisBinary) {}
#endif
