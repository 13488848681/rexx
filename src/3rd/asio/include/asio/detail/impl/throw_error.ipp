

#ifndef ASIO_DETAIL_IMPL_THROW_ERROR_IPP
#define ASIO_DETAIL_IMPL_THROW_ERROR_IPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include "asio/detail/config.hpp"
#include "asio/detail/throw_error.hpp"
#include "asio/detail/throw_exception.hpp"
#include "asio/system_error.hpp"

#include "asio/detail/push_options.hpp"

namespace asio {
namespace detail {

void do_throw_error(const asio::error_code& err)
{
  asio::system_error e(err);
  asio::detail::throw_exception(e);
}

void do_throw_error(const asio::error_code& err, const char* location)
{
#if defined(ASIO_MSVC) && defined(ASIO_HAS_STD_SYSTEM_ERROR)
  std::string what_msg = location;
  what_msg += ": ";
  what_msg += err.message();
  asio::system_error e(err, what_msg);
  asio::detail::throw_exception(e);
#else
  asio::system_error e(err, location);
  asio::detail::throw_exception(e);
#endif
}

}
}

#include "asio/detail/pop_options.hpp"

#endif
