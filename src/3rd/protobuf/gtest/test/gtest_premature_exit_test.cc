#include <stdio.h>

#include "gtest/gtest.h"

using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::internal::posix::GetEnv;
using ::testing::internal::posix::Stat;
using ::testing::internal::posix::StatStruct;

namespace {

// Is the TEST_PREMATURE_EXIT_FILE environment variable expected to be
// set?
const bool kTestPrematureExitFileEnvVarShouldBeSet = false;

class PrematureExitTest : public Test {
 public:
  // Returns true iff the given file exists.
  static bool FileExists(const char* filepath) {
    StatStruct stat;
    return Stat(filepath, &stat) == 0;
  }

 protected:
  PrematureExitTest() {
    premature_exit_file_path_ = GetEnv("TEST_PREMATURE_EXIT_FILE");

    // Normalize NULL to "" for ease of handling.
    if (premature_exit_file_path_ == NULL) {
      premature_exit_file_path_ = "";
    }
  }

  // Returns true iff the premature-exit file exists.
  bool PrematureExitFileExists() const {
    return FileExists(premature_exit_file_path_);
  }

  const char* premature_exit_file_path_;
};

typedef PrematureExitTest PrematureExitDeathTest;

// Tests that:
//   - the premature-exit file exists during the execution of a
//     death test (EXPECT_DEATH*), and
//   - a death test doesn't interfere with the main test process's
//     handling of the premature-exit file.
TEST_F(PrematureExitDeathTest, FileExistsDuringExecutionOfDeathTest) {
  if (*premature_exit_file_path_ == '\0') {
    return;
  }

  EXPECT_DEATH_IF_SUPPORTED({
      // If the file exists, crash the process such that the main test
      // process will catch the (expected) crash and report a success;
      // otherwise don't crash, which will cause the main test process
      // to report that the death test has failed.
      if (PrematureExitFileExists()) {
        exit(1);
      }
    }, "");
}

// Tests that TEST_PREMATURE_EXIT_FILE is set where it's expected to
// be set.
TEST_F(PrematureExitTest, TestPrematureExitFileEnvVarIsSet) {
  if (kTestPrematureExitFileEnvVarShouldBeSet) {
    const char* const filepath = GetEnv("TEST_PREMATURE_EXIT_FILE");
    ASSERT_TRUE(filepath != NULL);
    ASSERT_NE(*filepath, '\0');
  }
}

// Tests that the premature-exit file exists during the execution of a
// normal (non-death) test.
TEST_F(PrematureExitTest, PrematureExitFileExistsDuringTestExecution) {
  if (*premature_exit_file_path_ == '\0') {
    return;
  }

  EXPECT_TRUE(PrematureExitFileExists())
      << " file " << premature_exit_file_path_
      << " should exist during test execution, but doesn't.";
}

}  // namespace

int main(int argc, char **argv) {
  InitGoogleTest(&argc, argv);
  const int exit_code = RUN_ALL_TESTS();

  // Test that the premature-exit file is deleted upon return from
  // RUN_ALL_TESTS().
  const char* const filepath = GetEnv("TEST_PREMATURE_EXIT_FILE");
  if (filepath != NULL && *filepath != '\0') {
    if (PrematureExitTest::FileExists(filepath)) {
      printf(
          "File %s shouldn't exist after the test program finishes, but does.",
          filepath);
      return 1;
    }
  }

  return exit_code;
}
