#include "gtest/gtest.h"

#include "test/gtest-param-test_test.h"

#if GTEST_HAS_PARAM_TEST

using ::testing::Values;
using ::testing::internal::ParamGenerator;

// Tests that generators defined in a different translation unit
// are functional. The test using extern_gen is defined
// in gtest-param-test_test.cc.
ParamGenerator<int> extern_gen = Values(33);

// Tests that a parameterized test case can be defined in one translation unit
// and instantiated in another. The test is defined in gtest-param-test_test.cc
// and ExternalInstantiationTest fixture class is defined in
// gtest-param-test_test.h.
INSTANTIATE_TEST_CASE_P(MultiplesOf33,
                        ExternalInstantiationTest,
                        Values(33, 66));

// Tests that a parameterized test case can be instantiated
// in multiple translation units. Another instantiation is defined
// in gtest-param-test_test.cc and InstantiationInMultipleTranslaionUnitsTest
// fixture is defined in gtest-param-test_test.h
INSTANTIATE_TEST_CASE_P(Sequence2,
                        InstantiationInMultipleTranslaionUnitsTest,
                        Values(42*3, 42*4, 42*5));

#endif  // GTEST_HAS_PARAM_TEST
