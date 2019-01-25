
#ifndef ASIO_SSL_BASIC_CONTEXT_HPP
#define ASIO_SSL_BASIC_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"

#if defined(ASIO_ENABLE_OLD_SSL)
# include "asio/ssl/old/basic_context.hpp"
#endif // defined(ASIO_ENABLE_OLD_SSL)

#include "asio/detail/push_options.hpp"

namespace asio {
namespace ssl {

#if defined(ASIO_ENABLE_OLD_SSL)

using asio::ssl::old::basic_context;

#endif // defined(ASIO_ENABLE_OLD_SSL)

} // namespace ssl
} // namespace asio

#include "asio/detail/pop_options.hpp"

#endif // ASIO_SSL_BASIC_CONTEXT_HPP
