#include "gtest/gtest.h"

#include <stdio.h>                      // for fflush, fprintf, NULL, etc.
#include <stdlib.h>                     // for exit
#include <exception>                    // for set_terminate

// This terminate handler aborts the program using exit() rather than abort().
// This avoids showing pop-ups on Windows systems and core dumps on Unix-like
// ones.
void TerminateHandler() {
  fprintf(stderr, "%s\n", "Unhandled C++ exception terminating the program.");
  fflush(NULL);
  exit(1);
}

int main(int argc, char** argv) {
#if GTEST_HAS_EXCEPTIONS
  std::set_terminate(&TerminateHandler);
#endif
  testing::InitGoogleTest(&argc, argv);

  // We want to ensure that people can use Google Test assertions in
  // other testing frameworks, as long as they initialize Google Test
  // properly and set the throw-on-failure mode.  Therefore, we don't
  // use Google Test's constructs for defining and running tests
  // (e.g. TEST and RUN_ALL_TESTS) here.

  // In the throw-on-failure mode with exceptions disabled, this
  // assertion will cause the program to exit with a non-zero code.
  EXPECT_EQ(2, 3);

  // When not in the throw-on-failure mode, the control will reach
  // here.
  return 0;
}
