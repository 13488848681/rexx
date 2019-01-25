
#ifndef ASIO_HANDLER_INVOKE_HOOK_HPP
#define ASIO_HANDLER_INVOKE_HOOK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"

#include "asio/detail/push_options.hpp"

namespace asio {


/// Default handler invocation hook used for non-const function objects.
template <typename Function>
inline void asio_handler_invoke(Function& function, ...)
{
  function();
}

/// Default handler invocation hook used for const function objects.
template <typename Function>
inline void asio_handler_invoke(const Function& function, ...)
{
  Function tmp(function);
  tmp();
}

/*@}*/

} // namespace asio

#include "asio/detail/pop_options.hpp"

#endif // ASIO_HANDLER_INVOKE_HOOK_HPP
