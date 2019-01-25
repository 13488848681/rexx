
#ifndef HEADER_TESTUTIL_H
# define HEADER_TESTUTIL_H


# define SETUP_TEST_FIXTURE(TEST_FIXTURE_TYPE, set_up)\
        TEST_FIXTURE_TYPE fixture = set_up(TEST_CASE_NAME);\
        int result = 0

# define EXECUTE_TEST(execute_func, tear_down)\
        if (execute_func(fixture) != 0) result = 1;\
        tear_down(fixture);\
        return result

/*
 * TEST_CASE_NAME is defined as the name of the test case function where
 * possible; otherwise we get by with the file name and line number.
 */
# if __STDC_VERSION__ < 199901L
#  if defined(_MSC_VER)
#   define TEST_CASE_NAME __FUNCTION__
#  else
#   define testutil_stringify_helper(s) #s
#   define testutil_stringify(s) testutil_stringify_helper(s)
#   define TEST_CASE_NAME __FILE__ ":" testutil_stringify(__LINE__)
#  endif                        /* _MSC_VER */
# else
#  define TEST_CASE_NAME __func__
# endif                         /* __STDC_VERSION__ */

#endif                          /* HEADER_TESTUTIL_H */
