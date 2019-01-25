
#ifndef WEBSOCKETPP_CONFIG_ASIO_TLS_CLIENT_HPP
#define WEBSOCKETPP_CONFIG_ASIO_TLS_CLIENT_HPP

#include <websocketpp/config/core_client.hpp>
#include <websocketpp/transport/asio/endpoint.hpp>
#include <websocketpp/transport/asio/security/tls.hpp>

// Pull in non-tls config
#include <websocketpp/config/asio_no_tls_client.hpp>

// Define TLS config
namespace websocketpp {
namespace config {

/// Client config with asio transport and TLS enabled
struct asio_tls_client : public core_client {
    typedef asio_tls_client type;
    typedef core_client base;

    typedef base::concurrency_type concurrency_type;

    typedef base::request_type request_type;
    typedef base::response_type response_type;

    typedef base::message_type message_type;
    typedef base::con_msg_manager_type con_msg_manager_type;
    typedef base::endpoint_msg_manager_type endpoint_msg_manager_type;

    typedef base::alog_type alog_type;
    typedef base::elog_type elog_type;

    typedef base::rng_type rng_type;

    struct transport_config : public base::transport_config {
        typedef type::concurrency_type concurrency_type;
        typedef type::alog_type alog_type;
        typedef type::elog_type elog_type;
        typedef type::request_type request_type;
        typedef type::response_type response_type;
        typedef websocketpp::transport::asio::tls_socket::endpoint socket_type;
    };

    typedef websocketpp::transport::asio::endpoint<transport_config>
        transport_type;
};

} // namespace config
} // namespace websocketpp

#endif // WEBSOCKETPP_CONFIG_ASIO_TLS_CLIENT_HPP
