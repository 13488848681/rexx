
#ifndef ASIO_CONNECT_HPP
#define ASIO_CONNECT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"
#include "asio/async_result.hpp"
#include "asio/basic_socket.hpp"
#include "asio/error.hpp"

#include "asio/detail/push_options.hpp"

namespace asio {

/**
 * @defgroup connect asio::connect
 *
 * @brief Establishes a socket connection by trying each endpoint in a sequence.
 */
/*@{*/

/// Establishes a socket connection by trying each endpoint in a sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c connect member
 * function, once for each endpoint in the sequence, until a connection is
 * successfully established.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param begin An iterator pointing to the start of a sequence of endpoints.
 *
 * @returns On success, an iterator denoting the successfully connected
 * endpoint. Otherwise, the end iterator.
 *
 * @throws asio::system_error Thrown on failure. If the sequence is
 * empty, the associated @c error_code is asio::error::not_found.
 * Otherwise, contains the error from the last connection attempt.
 *
 * @note This overload assumes that a default constructed object of type @c
 * Iterator represents the end of the sequence. This is a valid assumption for
 * iterator types such as @c asio::ip::tcp::resolver::iterator.
 *
 * @par Example
 * @code tcp::resolver r(io_service);
 * tcp::resolver::query q("host", "service");
 * tcp::socket s(io_service);
 * asio::connect(s, r.resolve(q)); @endcode
 */
template <typename Protocol, typename SocketService, typename Iterator>
Iterator connect(basic_socket<Protocol, SocketService>& s, Iterator begin);

/// Establishes a socket connection by trying each endpoint in a sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c connect member
 * function, once for each endpoint in the sequence, until a connection is
 * successfully established.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param begin An iterator pointing to the start of a sequence of endpoints.
 *
 * @param ec Set to indicate what error occurred, if any. If the sequence is
 * empty, set to asio::error::not_found. Otherwise, contains the error
 * from the last connection attempt.
 *
 * @returns On success, an iterator denoting the successfully connected
 * endpoint. Otherwise, the end iterator.
 *
 * @note This overload assumes that a default constructed object of type @c
 * Iterator represents the end of the sequence. This is a valid assumption for
 * iterator types such as @c asio::ip::tcp::resolver::iterator.
 *
 * @par Example
 * @code tcp::resolver r(io_service);
 * tcp::resolver::query q("host", "service");
 * tcp::socket s(io_service);
 * asio::error_code ec;
 * asio::connect(s, r.resolve(q), ec);
 * if (ec)
 * {
 *   // An error occurred.
 * } @endcode
 */
template <typename Protocol, typename SocketService, typename Iterator>
Iterator connect(basic_socket<Protocol, SocketService>& s,
    Iterator begin, asio::error_code& ec);

/// Establishes a socket connection by trying each endpoint in a sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c connect member
 * function, once for each endpoint in the sequence, until a connection is
 * successfully established.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param begin An iterator pointing to the start of a sequence of endpoints.
 *
 * @param end An iterator pointing to the end of a sequence of endpoints.
 *
 * @returns On success, an iterator denoting the successfully connected
 * endpoint. Otherwise, the end iterator.
 *
 * @throws asio::system_error Thrown on failure. If the sequence is
 * empty, the associated @c error_code is asio::error::not_found.
 * Otherwise, contains the error from the last connection attempt.
 *
 * @par Example
 * @code tcp::resolver r(io_service);
 * tcp::resolver::query q("host", "service");
 * tcp::resolver::iterator i = r.resolve(q), end;
 * tcp::socket s(io_service);
 * asio::connect(s, i, end); @endcode
 */
template <typename Protocol, typename SocketService, typename Iterator>
Iterator connect(basic_socket<Protocol, SocketService>& s,
    Iterator begin, Iterator end);

/// Establishes a socket connection by trying each endpoint in a sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c connect member
 * function, once for each endpoint in the sequence, until a connection is
 * successfully established.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param begin An iterator pointing to the start of a sequence of endpoints.
 *
 * @param end An iterator pointing to the end of a sequence of endpoints.
 *
 * @param ec Set to indicate what error occurred, if any. If the sequence is
 * empty, set to asio::error::not_found. Otherwise, contains the error
 * from the last connection attempt.
 *
 * @returns On success, an iterator denoting the successfully connected
 * endpoint. Otherwise, the end iterator.
 *
 * @par Example
 * @code tcp::resolver r(io_service);
 * tcp::resolver::query q("host", "service");
 * tcp::resolver::iterator i = r.resolve(q), end;
 * tcp::socket s(io_service);
 * asio::error_code ec;
 * asio::connect(s, i, end, ec);
 * if (ec)
 * {
 *   // An error occurred.
 * } @endcode
 */
template <typename Protocol, typename SocketService, typename Iterator>
Iterator connect(basic_socket<Protocol, SocketService>& s,
    Iterator begin, Iterator end, asio::error_code& ec);


template <typename Protocol, typename SocketService,
    typename Iterator, typename ConnectCondition>
Iterator connect(basic_socket<Protocol, SocketService>& s,
    Iterator begin, ConnectCondition connect_condition);

template <typename Protocol, typename SocketService,
    typename Iterator, typename ConnectCondition>
Iterator connect(basic_socket<Protocol, SocketService>& s, Iterator begin,
    ConnectCondition connect_condition, asio::error_code& ec);


template <typename Protocol, typename SocketService,
    typename Iterator, typename ConnectCondition>
Iterator connect(basic_socket<Protocol, SocketService>& s, Iterator begin,
    Iterator end, ConnectCondition connect_condition);


template <typename Protocol, typename SocketService,
    typename Iterator, typename ConnectCondition>
Iterator connect(basic_socket<Protocol, SocketService>& s,
    Iterator begin, Iterator end, ConnectCondition connect_condition,
    asio::error_code& ec);


template <typename Protocol, typename SocketService,
    typename Iterator, typename ComposedConnectHandler>
ASIO_INITFN_RESULT_TYPE(ComposedConnectHandler,
    void (asio::error_code, Iterator))
async_connect(basic_socket<Protocol, SocketService>& s,
    Iterator begin, ASIO_MOVE_ARG(ComposedConnectHandler) handler);


template <typename Protocol, typename SocketService,
    typename Iterator, typename ComposedConnectHandler>
ASIO_INITFN_RESULT_TYPE(ComposedConnectHandler,
    void (asio::error_code, Iterator))
async_connect(basic_socket<Protocol, SocketService>& s,
    Iterator begin, Iterator end,
    ASIO_MOVE_ARG(ComposedConnectHandler) handler);


template <typename Protocol, typename SocketService, typename Iterator,
    typename ConnectCondition, typename ComposedConnectHandler>
ASIO_INITFN_RESULT_TYPE(ComposedConnectHandler,
    void (asio::error_code, Iterator))
async_connect(basic_socket<Protocol, SocketService>& s, Iterator begin,
    ConnectCondition connect_condition,
    ASIO_MOVE_ARG(ComposedConnectHandler) handler);


template <typename Protocol, typename SocketService, typename Iterator,
    typename ConnectCondition, typename ComposedConnectHandler>
ASIO_INITFN_RESULT_TYPE(ComposedConnectHandler,
    void (asio::error_code, Iterator))
async_connect(basic_socket<Protocol, SocketService>& s,
    Iterator begin, Iterator end, ConnectCondition connect_condition,
    ASIO_MOVE_ARG(ComposedConnectHandler) handler);

/*@}*/

} // namespace asio

#include "asio/detail/pop_options.hpp"

#include "asio/impl/connect.hpp"

#endif
