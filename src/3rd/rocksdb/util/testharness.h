
#pragma once

#include <gtest/gtest.h>

#include <string>
#include "rocksdb/env.h"

namespace rocksdb {
namespace test {

// Return the directory to use for temporary storage.
std::string TmpDir(Env* env = Env::Default());

// Return a randomization seed for this run.  Typically returns the
// same number on repeated invocations of this binary, but automated
// runs may be able to vary the seed.
int RandomSeed();

::testing::AssertionResult AssertStatus(const char* s_expr, const Status& s);

#define ASSERT_OK(s) ASSERT_PRED_FORMAT1(rocksdb::test::AssertStatus, s)
#define ASSERT_NOK(s) ASSERT_FALSE((s).ok())
#define EXPECT_OK(s) EXPECT_PRED_FORMAT1(rocksdb::test::AssertStatus, s)
#define EXPECT_NOK(s) EXPECT_FALSE((s).ok())

}  // namespace test
}  // namespace rocksdb
