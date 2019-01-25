

#ifndef WEBSOCKETPP_COMMON_ASIO_SSL_HPP
#define WEBSOCKETPP_COMMON_ASIO_SSL_HPP

#ifdef ASIO_STANDALONE
    #include <3rd/asio/include/asio/ssl.hpp>
#else
    #include <boost/asio/ssl.hpp>
#endif

#endif // WEBSOCKETPP_COMMON_ASIO_SSL_HPP
