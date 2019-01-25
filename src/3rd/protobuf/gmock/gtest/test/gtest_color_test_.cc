
#include <stdio.h>

#include "gtest/gtest.h"

// Indicates that this translation unit is part of Google Test's
// implementation.  It must come before gtest-internal-inl.h is
// included, or there will be a compiler error.  This trick is to
// prevent a user from accidentally including gtest-internal-inl.h in
// his code.
#define GTEST_IMPLEMENTATION_ 1
#include "src/gtest-internal-inl.h"
#undef GTEST_IMPLEMENTATION_

using testing::internal::ShouldUseColor;

// The purpose of this is to ensure that the UnitTest singleton is
// created before main() is entered, and thus that ShouldUseColor()
// works the same way as in a real Google-Test-based test.  We don't actual
// run the TEST itself.
TEST(GTestColorTest, Dummy) {
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);

  if (ShouldUseColor(true)) {
    // Google Test decides to use colors in the output (assuming it
    // goes to a TTY).
    printf("YES\n");
    return 1;
  } else {
    // Google Test decides not to use colors in the output.
    printf("NO\n");
    return 0;
  }
}
