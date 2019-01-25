
#ifndef ASIO_DETAIL_IMPL_WIN_MUTEX_IPP
#define ASIO_DETAIL_IMPL_WIN_MUTEX_IPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include "asio/detail/config.hpp"

#if defined(ASIO_WINDOWS)

#include "asio/detail/throw_error.hpp"
#include "asio/detail/win_mutex.hpp"
#include "asio/error.hpp"

#include "asio/detail/push_options.hpp"

namespace asio {
namespace detail {

win_mutex::win_mutex()
{
  int error = do_init();
  asio::error_code ec(error,
      asio::error::get_system_category());
  asio::detail::throw_error(ec, "mutex");
}

int win_mutex::do_init()
{
#if defined(__MINGW32__)
# if defined(UNDER_CE)
  ::InitializeCriticalSection(&crit_section_);
# else
  if (!::InitializeCriticalSectionAndSpinCount(&crit_section_, 0x80000000))
    return ::GetLastError();
# endif
  return 0;
#else
  __try
  {
# if defined(UNDER_CE)
    ::InitializeCriticalSection(&crit_section_);
# else
    if (!::InitializeCriticalSectionAndSpinCount(&crit_section_, 0x80000000))
      return ::GetLastError();
# endif
  }
  __except(GetExceptionCode() == STATUS_NO_MEMORY
      ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
  {
    return ERROR_OUTOFMEMORY;
  }

  return 0;
#endif
}

}
}

#include "asio/detail/pop_options.hpp"

#endif

#endif
