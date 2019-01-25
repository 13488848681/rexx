
#define BOOST_TEST_MODULE hybi_00_processor
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <string>

#include <websocketpp/processors/hybi00.hpp>
#include <websocketpp/http/request.hpp>
#include <websocketpp/http/response.hpp>


BOOST_AUTO_TEST_CASE( exact_match ) {
    websocketpp::http::parser::request r;
    websocketpp::http::parser::response response;
    websocketpp::processor::hybi00<websocketpp::http::parser::request,websocketpp::http::parser::response> p(false);

    std::string handshake = "GET / HTTP/1.1\r\nHost: www.example.com\r\nConnection: upgrade\r\nUpgrade: websocket\r\nOrigin: http://example.com\r\nSec-WebSocket-Key1: 3e6b263  4 17 80\r\nSec-WebSocket-Key2: 17  9 G`ZD9   2 2b 7X 3 /r90\r\n\r\n";

    r.consume(handshake.c_str(),handshake.size());
    r.replace_header("Sec-WebSocket-Key3","WjN}|M(6");

    BOOST_CHECK(websocketpp::processor::is_websocket_handshake(r));
    BOOST_CHECK(websocketpp::processor::get_websocket_version(r) == p.get_version());
    BOOST_CHECK(p.validate_handshake(r));

    websocketpp::uri_ptr u;
    bool exception;

    try {
        u = p.get_uri(r);
    } catch (const websocketpp::uri_exception& e) {
        exception = true;
    }

    BOOST_CHECK(exception == false);
    BOOST_CHECK(u->get_secure() == false);
    BOOST_CHECK(u->get_host() == "www.example.com");
    BOOST_CHECK(u->get_resource() == "/");
    BOOST_CHECK(u->get_port() == websocketpp::URI_DEFAULT_PORT);

    p.process_handshake(r,response);

    BOOST_CHECK(response.get_header("Connection") == "Upgrade");
    BOOST_CHECK(response.get_header("Upgrade") == "websocket");
    BOOST_CHECK(response.get_header("Sec-WebSocket-Origin") == "http://example.com");

    BOOST_CHECK(response.get_header("Sec-WebSocket-Location") == "ws://www.example.com/");
    BOOST_CHECK(response.get_header("Sec-WebSocket-Key3") == "n`9eBk9z$R8pOtVb");
}

BOOST_AUTO_TEST_CASE( non_get_method ) {
    websocketpp::http::parser::request r;
    websocketpp::processor::hybi00<websocketpp::http::parser::request,websocketpp::http::parser::response> p(false);

    std::string handshake = "POST / HTTP/1.1\r\nHost: www.example.com\r\nConnection: upgrade\r\nUpgrade: websocket\r\nSec-WebSocket-Key1: 3e6b263  4 17 80\r\nSec-WebSocket-Key2: 17  9 G`ZD9   2 2b 7X 3 /r90\r\n\r\n";

    r.consume(handshake.c_str(),handshake.size());
    r.replace_header("Sec-WebSocket-Key3","janelle!");

    BOOST_CHECK(websocketpp::processor::is_websocket_handshake(r));
    BOOST_CHECK(websocketpp::processor::get_websocket_version(r) == p.get_version());
    BOOST_CHECK(!p.validate_handshake(r));
}

BOOST_AUTO_TEST_CASE( old_http_version ) {
    websocketpp::http::parser::request r;
    websocketpp::processor::hybi00<websocketpp::http::parser::request,websocketpp::http::parser::response> p(false);

    std::string handshake = "GET / HTTP/1.0\r\nHost: www.example.com\r\nConnection: upgrade\r\nUpgrade: websocket\r\nSec-WebSocket-Key1: 3e6b263  4 17 80\r\nSec-WebSocket-Key2: 17  9 G`ZD9   2 2b 7X 3 /r90\r\n\r\n";

    r.consume(handshake.c_str(),handshake.size());
    r.replace_header("Sec-WebSocket-Key3","janelle!");

    BOOST_CHECK(websocketpp::processor::is_websocket_handshake(r));
    BOOST_CHECK(websocketpp::processor::get_websocket_version(r) == p.get_version());
    BOOST_CHECK(!p.validate_handshake(r));
}

BOOST_AUTO_TEST_CASE( missing_handshake_key1 ) {
    websocketpp::http::parser::request r;
    websocketpp::processor::hybi00<websocketpp::http::parser::request,websocketpp::http::parser::response> p(false);

    std::string handshake = "GET / HTTP/1.1\r\nHost: www.example.com\r\nConnection: upgrade\r\nUpgrade: websocket\r\nSec-WebSocket-Key1: 3e6b263  4 17 80\r\n\r\n";

    r.consume(handshake.c_str(),handshake.size());
    r.replace_header("Sec-WebSocket-Key3","janelle!");

    BOOST_CHECK(websocketpp::processor::is_websocket_handshake(r));
    BOOST_CHECK(websocketpp::processor::get_websocket_version(r) == p.get_version());
    BOOST_CHECK(!p.validate_handshake(r));
}

BOOST_AUTO_TEST_CASE( missing_handshake_key2 ) {
    websocketpp::http::parser::request r;
    websocketpp::processor::hybi00<websocketpp::http::parser::request,websocketpp::http::parser::response> p(false);

    std::string handshake = "GET / HTTP/1.1\r\nHost: www.example.com\r\nConnection: upgrade\r\nUpgrade: websocket\r\nSec-WebSocket-Key2: 17  9 G`ZD9   2 2b 7X 3 /r90\r\n\r\n";

    r.consume(handshake.c_str(),handshake.size());
    r.replace_header("Sec-WebSocket-Key3","janelle!");

    BOOST_CHECK(websocketpp::processor::is_websocket_handshake(r));
    BOOST_CHECK(websocketpp::processor::get_websocket_version(r) == p.get_version());
    BOOST_CHECK(!p.validate_handshake(r));
}

BOOST_AUTO_TEST_CASE( bad_host ) {
    websocketpp::http::parser::request r;
    websocketpp::processor::hybi00<websocketpp::http::parser::request,websocketpp::http::parser::response> p(false);
    websocketpp::uri_ptr u;
    bool exception = false;

    std::string handshake = "GET / HTTP/1.1\r\nHost: www.example.com:70000\r\nConnection: upgrade\r\nUpgrade: websocket\r\nSec-WebSocket-Key2: 17  9 G`ZD9   2 2b 7X 3 /r90\r\n\r\n";

    r.consume(handshake.c_str(),handshake.size());
    r.replace_header("Sec-WebSocket-Key3","janelle!");

    BOOST_CHECK(websocketpp::processor::is_websocket_handshake(r));
    BOOST_CHECK(websocketpp::processor::get_websocket_version(r) == p.get_version());
    BOOST_CHECK(!p.validate_handshake(r));

    try {
        u = p.get_uri(r);
    } catch (const websocketpp::uri_exception& e) {
        exception = true;
    }

    BOOST_CHECK(exception == true);
}
