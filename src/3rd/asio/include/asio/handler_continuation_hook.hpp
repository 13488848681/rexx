
#ifndef ASIO_HANDLER_CONTINUATION_HOOK_HPP
#define ASIO_HANDLER_CONTINUATION_HOOK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"

#include "asio/detail/push_options.hpp"

namespace asio {


inline bool asio_handler_is_continuation(...)
{
  return false;
}

} // namespace asio

#include "asio/detail/pop_options.hpp"

#endif // ASIO_HANDLER_CONTINUATION_HOOK_HPP
