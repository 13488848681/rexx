
//#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE utility
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <string>

#include <websocketpp/utilities.hpp>

BOOST_AUTO_TEST_SUITE ( utility )

BOOST_AUTO_TEST_CASE( substr_found ) {
    std::string haystack = "abc123";
    std::string needle = "abc";

    BOOST_CHECK(websocketpp::utility::ci_find_substr(haystack,needle) ==haystack.begin());
}

BOOST_AUTO_TEST_CASE( substr_found_ci ) {
    std::string haystack = "abc123";
    std::string needle = "aBc";

    BOOST_CHECK(websocketpp::utility::ci_find_substr(haystack,needle) ==haystack.begin());
}

BOOST_AUTO_TEST_CASE( substr_not_found ) {
    std::string haystack = "abd123";
    std::string needle = "abcd";

    BOOST_CHECK(websocketpp::utility::ci_find_substr(haystack,needle) == haystack.end());
}

BOOST_AUTO_TEST_CASE( to_lower ) {
    std::string in = "AbCd";

    BOOST_CHECK_EQUAL(websocketpp::utility::to_lower(in), "abcd");
}

BOOST_AUTO_TEST_CASE( string_replace_all ) {
    std::string source = "foo \"bar\" baz";
    std::string dest = "foo \\\"bar\\\" baz";

    using websocketpp::utility::string_replace_all;
    BOOST_CHECK_EQUAL(string_replace_all(source,"\"","\\\""),dest);
}

BOOST_AUTO_TEST_SUITE_END()
