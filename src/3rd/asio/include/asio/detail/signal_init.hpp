
#ifndef ASIO_DETAIL_SIGNAL_INIT_HPP
#define ASIO_DETAIL_SIGNAL_INIT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"

#if !defined(ASIO_WINDOWS) && !defined(__CYGWIN__)

#include <csignal>

#include "asio/detail/push_options.hpp"

namespace asio {
namespace detail {

template <int Signal = SIGPIPE>
class signal_init
{
public:
  // Constructor.
  signal_init()
  {
    std::signal(Signal, SIG_IGN);
  }
};

} // namespace detail
} // namespace asio

#include "asio/detail/pop_options.hpp"

#endif // !defined(ASIO_WINDOWS) && !defined(__CYGWIN__)

#endif // ASIO_DETAIL_SIGNAL_INIT_HPP
