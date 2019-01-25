
#include "gtest/gtest-death-test.h"
#include "gtest/gtest.h"

#if GTEST_HAS_DEATH_TEST

# if GTEST_HAS_SEH
#  include <windows.h>          // For RaiseException().
# endif

# include "gtest/gtest-spi.h"

# if GTEST_HAS_EXCEPTIONS

#  include <exception>  // For std::exception.

// Tests that death tests report thrown exceptions as failures and that the
// exceptions do not escape death test macros.
TEST(CxxExceptionDeathTest, ExceptionIsFailure) {
  try {
    EXPECT_NONFATAL_FAILURE(EXPECT_DEATH(throw 1, ""), "threw an exception");
  } catch (...) {  // NOLINT
    FAIL() << "An exception escaped a death test macro invocation "
           << "with catch_exceptions "
           << (testing::GTEST_FLAG(catch_exceptions) ? "enabled" : "disabled");
  }
}

class TestException : public std::exception {
 public:
  virtual const char* what() const throw() { return "exceptional message"; }
};

TEST(CxxExceptionDeathTest, PrintsMessageForStdExceptions) {
  // Verifies that the exception message is quoted in the failure text.
  EXPECT_NONFATAL_FAILURE(EXPECT_DEATH(throw TestException(), ""),
                          "exceptional message");
  // Verifies that the location is mentioned in the failure text.
  EXPECT_NONFATAL_FAILURE(EXPECT_DEATH(throw TestException(), ""),
                          "gtest-death-test_ex_test.cc");
}
# endif  // GTEST_HAS_EXCEPTIONS

# if GTEST_HAS_SEH
// Tests that enabling interception of SEH exceptions with the
// catch_exceptions flag does not interfere with SEH exceptions being
// treated as death by death tests.
TEST(SehExceptionDeasTest, CatchExceptionsDoesNotInterfere) {
  EXPECT_DEATH(RaiseException(42, 0x0, 0, NULL), "")
      << "with catch_exceptions "
      << (testing::GTEST_FLAG(catch_exceptions) ? "enabled" : "disabled");
}
# endif

#endif  // GTEST_HAS_DEATH_TEST

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  testing::GTEST_FLAG(catch_exceptions) = GTEST_ENABLE_CATCH_EXCEPTIONS_ != 0;
  return RUN_ALL_TESTS();
}
