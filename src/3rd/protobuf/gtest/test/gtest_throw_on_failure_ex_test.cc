#include "gtest/gtest.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdexcept>

// Prints the given failure message and exits the program with
// non-zero.  We use this instead of a Google Test assertion to
// indicate a failure, as the latter is been tested and cannot be
// relied on.
void Fail(const char* msg) {
  printf("FAILURE: %s\n", msg);
  fflush(stdout);
  exit(1);
}

// Tests that an assertion failure throws a subclass of
// std::runtime_error.
void TestFailureThrowsRuntimeError() {
  testing::GTEST_FLAG(throw_on_failure) = true;

  // A successful assertion shouldn't throw.
  try {
    EXPECT_EQ(3, 3);
  } catch(...) {
    Fail("A successful assertion wrongfully threw.");
  }

  // A failed assertion should throw a subclass of std::runtime_error.
  try {
    EXPECT_EQ(2, 3) << "Expected failure";
  } catch(const std::runtime_error& e) {
    if (strstr(e.what(), "Expected failure") != NULL)
      return;

    printf("%s",
           "A failed assertion did throw an exception of the right type, "
           "but the message is incorrect.  Instead of containing \"Expected "
           "failure\", it is:\n");
    Fail(e.what());
  } catch(...) {
    Fail("A failed assertion threw the wrong type of exception.");
  }
  Fail("A failed assertion should've thrown but didn't.");
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);

  // We want to ensure that people can use Google Test assertions in
  // other testing frameworks, as long as they initialize Google Test
  // properly and set the thrown-on-failure mode.  Therefore, we don't
  // use Google Test's constructs for defining and running tests
  // (e.g. TEST and RUN_ALL_TESTS) here.

  TestFailureThrowsRuntimeError();
  return 0;
}
