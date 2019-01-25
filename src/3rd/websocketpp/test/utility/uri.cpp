
//#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE uri
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <string>

#include <websocketpp/uri.hpp>

// Test a regular valid ws URI
BOOST_AUTO_TEST_CASE( uri_valid ) {
    websocketpp::uri uri("ws://localhost:9000/chat");

    BOOST_CHECK( uri.get_valid() );
    BOOST_CHECK( !uri.get_secure() );
    BOOST_CHECK_EQUAL( uri.get_scheme(), "ws");
    BOOST_CHECK_EQUAL( uri.get_host(), "localhost");
    BOOST_CHECK_EQUAL( uri.get_port(), 9000 );
    BOOST_CHECK_EQUAL( uri.get_resource(), "/chat" );
    BOOST_CHECK_EQUAL( uri.get_query(), "" );
}

// Test a regular valid ws URI
BOOST_AUTO_TEST_CASE( uri_valid_no_port_unsecure ) {
    websocketpp::uri uri("ws://localhost/chat");

    BOOST_CHECK( uri.get_valid() );
    BOOST_CHECK( !uri.get_secure() );
    BOOST_CHECK_EQUAL( uri.get_scheme(), "ws");
    BOOST_CHECK_EQUAL( uri.get_host(), "localhost");
    BOOST_CHECK_EQUAL( uri.get_port(), 80 );
    BOOST_CHECK_EQUAL( uri.get_resource(), "/chat" );
}

// Valid URI with no port (secure)
BOOST_AUTO_TEST_CASE( uri_valid_no_port_secure ) {
    websocketpp::uri uri("wss://localhost/chat");

    BOOST_CHECK( uri.get_valid() );
    BOOST_CHECK( uri.get_secure() );
    BOOST_CHECK_EQUAL( uri.get_scheme(), "wss");
    BOOST_CHECK_EQUAL( uri.get_host(), "localhost");
    BOOST_CHECK_EQUAL( uri.get_port(), 443 );
    BOOST_CHECK_EQUAL( uri.get_resource(), "/chat" );
}

// Valid URI with no resource
BOOST_AUTO_TEST_CASE( uri_valid_no_resource ) {
    websocketpp::uri uri("wss://localhost:9000");

    BOOST_CHECK( uri.get_valid() );
    BOOST_CHECK( uri.get_secure() );
    BOOST_CHECK_EQUAL( uri.get_scheme(), "wss");
    BOOST_CHECK_EQUAL( uri.get_host(), "localhost");
    BOOST_CHECK_EQUAL( uri.get_port(), 9000 );
    BOOST_CHECK_EQUAL( uri.get_resource(), "/" );
}

// Valid URI IPv6 Literal
BOOST_AUTO_TEST_CASE( uri_valid_ipv6_literal ) {
    websocketpp::uri uri("wss://[::1]:9000/chat");

    BOOST_CHECK( uri.get_valid() );
    BOOST_CHECK( uri.get_secure() );
    BOOST_CHECK_EQUAL( uri.get_scheme(), "wss");
    BOOST_CHECK_EQUAL( uri.get_host(), "::1");
    BOOST_CHECK_EQUAL( uri.get_port(), 9000 );
    BOOST_CHECK_EQUAL( uri.get_resource(), "/chat" );
}

// Valid URI with more complicated host
BOOST_AUTO_TEST_CASE( uri_valid_2 ) {
    websocketpp::uri uri("wss://thor-websocket.zaphoyd.net:88/");

    BOOST_CHECK( uri.get_valid() );
    BOOST_CHECK( uri.get_secure() );
    BOOST_CHECK_EQUAL( uri.get_scheme(), "wss");
    BOOST_CHECK_EQUAL( uri.get_host(), "thor-websocket.zaphoyd.net");
    BOOST_CHECK_EQUAL( uri.get_port(), 88 );
    BOOST_CHECK_EQUAL( uri.get_resource(), "/" );
}


// Invalid URI (port too long)
BOOST_AUTO_TEST_CASE( uri_invalid_long_port ) {
    websocketpp::uri uri("wss://localhost:900000/chat");

    BOOST_CHECK( !uri.get_valid() );
}

// Invalid URI (bogus scheme method)
BOOST_AUTO_TEST_CASE( uri_invalid_scheme ) {
    websocketpp::uri uri("foo://localhost:9000/chat");

    BOOST_CHECK( !uri.get_valid() );
}

// Valid URI (http method)
BOOST_AUTO_TEST_CASE( uri_http_scheme ) {
    websocketpp::uri uri("http://localhost:9000/chat");

    BOOST_CHECK( uri.get_valid() );
    BOOST_CHECK( !uri.get_secure() );
    BOOST_CHECK_EQUAL( uri.get_scheme(), "http");
    BOOST_CHECK_EQUAL( uri.get_host(), "localhost");
    BOOST_CHECK_EQUAL( uri.get_port(), 9000 );
    BOOST_CHECK_EQUAL( uri.get_resource(), "/chat" );
}

// Valid URI IPv4 literal
BOOST_AUTO_TEST_CASE( uri_valid_ipv4_literal ) {
    websocketpp::uri uri("wss://127.0.0.1:9000/chat");

    BOOST_CHECK( uri.get_valid() );
    BOOST_CHECK( uri.get_secure() );
    BOOST_CHECK_EQUAL( uri.get_scheme(), "wss");
    BOOST_CHECK_EQUAL( uri.get_host(), "127.0.0.1");
    BOOST_CHECK_EQUAL( uri.get_port(), 9000 );
    BOOST_CHECK_EQUAL( uri.get_resource(), "/chat" );
}

// Valid URI complicated resource path
BOOST_AUTO_TEST_CASE( uri_valid_3 ) {
    websocketpp::uri uri("wss://localhost:9000/chat/foo/bar");

    BOOST_CHECK( uri.get_valid() );
    BOOST_CHECK( uri.get_secure() );
    BOOST_CHECK_EQUAL( uri.get_scheme(), "wss");
    BOOST_CHECK_EQUAL( uri.get_host(), "localhost");
    BOOST_CHECK_EQUAL( uri.get_port(), 9000 );
    BOOST_CHECK_EQUAL( uri.get_resource(), "/chat/foo/bar" );
}

// Invalid URI broken method separator
BOOST_AUTO_TEST_CASE( uri_invalid_method_separator ) {
    websocketpp::uri uri("wss:/localhost:9000/chat");

    BOOST_CHECK( !uri.get_valid() );
}

// Invalid URI port > 65535
BOOST_AUTO_TEST_CASE( uri_invalid_gt_16_bit_port ) {
    websocketpp::uri uri("wss:/localhost:70000/chat");

    BOOST_CHECK( !uri.get_valid() );
}

// Invalid URI includes uri fragment
BOOST_AUTO_TEST_CASE( uri_invalid_fragment ) {
    websocketpp::uri uri("wss:/localhost:70000/chat#foo");

    BOOST_CHECK( !uri.get_valid() );
}

// Invalid URI with no brackets around IPv6 literal
BOOST_AUTO_TEST_CASE( uri_invalid_bad_v6_literal_1 ) {
    websocketpp::uri uri("wss://::1/chat");

    BOOST_CHECK( !uri.get_valid() );
}

// Invalid URI with port and no brackets around IPv6 literal
BOOST_AUTO_TEST_CASE( uri_invalid_bad_v6_literal_2 ) {
    websocketpp::uri uri("wss://::1:2009/chat");

    BOOST_CHECK( !uri.get_valid() );
}

// Valid URI complicated resource path with query
BOOST_AUTO_TEST_CASE( uri_valid_4 ) {
    websocketpp::uri uri("wss://localhost:9000/chat/foo/bar?foo=bar");

    BOOST_CHECK( uri.get_valid() );
    BOOST_CHECK( uri.get_secure() );
    BOOST_CHECK_EQUAL( uri.get_scheme(), "wss" );
    BOOST_CHECK_EQUAL( uri.get_host(), "localhost");
    BOOST_CHECK_EQUAL( uri.get_port(), 9000 );
    BOOST_CHECK_EQUAL( uri.get_resource(), "/chat/foo/bar?foo=bar" );
    BOOST_CHECK_EQUAL( uri.get_query(), "foo=bar" );
}

// Valid URI with a mapped v4 ipv6 literal
BOOST_AUTO_TEST_CASE( uri_valid_v4_mapped ) {
    websocketpp::uri uri("wss://[0000:0000:0000:0000:0000:0000:192.168.1.1]:9000/");

    BOOST_CHECK( uri.get_valid() );
    BOOST_CHECK( uri.get_secure() );
    BOOST_CHECK_EQUAL( uri.get_scheme(), "wss" );
    BOOST_CHECK_EQUAL( uri.get_host(), "0000:0000:0000:0000:0000:0000:192.168.1.1");
    BOOST_CHECK_EQUAL( uri.get_port(), 9000 );
    BOOST_CHECK_EQUAL( uri.get_resource(), "/" );
}

// Valid URI with a v6 address with mixed case
BOOST_AUTO_TEST_CASE( uri_valid_v6_mixed_case ) {
    websocketpp::uri uri("wss://[::10aB]:9000/");

    BOOST_CHECK( uri.get_valid() == true );
    BOOST_CHECK( uri.get_secure() == true );
    BOOST_CHECK_EQUAL( uri.get_scheme(), "wss" );
    BOOST_CHECK_EQUAL( uri.get_host(), "::10aB");
    BOOST_CHECK_EQUAL( uri.get_port(), 9000 );
    BOOST_CHECK_EQUAL( uri.get_resource(), "/" );
}

// Valid URI with a v6 address with mixed case
BOOST_AUTO_TEST_CASE( uri_invalid_no_scheme ) {
    websocketpp::uri uri("myserver.com");

    BOOST_CHECK( !uri.get_valid() );
}

// Invalid IPv6 literal
/*BOOST_AUTO_TEST_CASE( uri_invalid_v6_nonhex ) {
    websocketpp::uri uri("wss://[g::1]:9000/");

    BOOST_CHECK( uri.get_valid() == false );
}*/

// TODO: tests for the other two constructors
