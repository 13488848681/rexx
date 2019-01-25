

#ifndef ASIO_DETAIL_IMPL_POSIX_EVENT_IPP
#define ASIO_DETAIL_IMPL_POSIX_EVENT_IPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include "asio/detail/config.hpp"

#if defined(ASIO_HAS_PTHREADS)

#include "asio/detail/posix_event.hpp"
#include "asio/detail/throw_error.hpp"
#include "asio/error.hpp"

#include "asio/detail/push_options.hpp"

namespace asio {
namespace detail {

posix_event::posix_event()
  : state_(0)
{
  int error = ::pthread_cond_init(&cond_, 0);
  asio::error_code ec(error,
      asio::error::get_system_category());
  asio::detail::throw_error(ec, "event");
}

}
}

#include "asio/detail/pop_options.hpp"

#endif

#endif
