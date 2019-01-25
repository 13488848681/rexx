
#ifndef ASIO_DETAIL_IMPL_WIN_STATIC_MUTEX_IPP
#define ASIO_DETAIL_IMPL_WIN_STATIC_MUTEX_IPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include "asio/detail/config.hpp"

#if defined(ASIO_WINDOWS)

#include <cstdio>
#include "asio/detail/throw_error.hpp"
#include "asio/detail/win_static_mutex.hpp"
#include "asio/error.hpp"

#include "asio/detail/push_options.hpp"

namespace asio {
namespace detail {

void win_static_mutex::init()
{
  int error = do_init();
  asio::error_code ec(error,
      asio::error::get_system_category());
  asio::detail::throw_error(ec, "static_mutex");
}

int win_static_mutex::do_init()
{
  using namespace std;
  wchar_t mutex_name[128];
#if defined(ASIO_HAS_SECURE_RTL)
  swprintf_s(
#else
  _snwprintf(
#endif
      mutex_name, 128, L"asio-58CCDC44-6264-4842-90C2-F3C545CB8AA7-%u-%p",
      static_cast<unsigned int>(::GetCurrentProcessId()), this);

  HANDLE mutex = ::CreateMutexW(0, TRUE, mutex_name);
  DWORD last_error = ::GetLastError();
  if (mutex == 0)
    return ::GetLastError();

  if (last_error == ERROR_ALREADY_EXISTS)
    ::WaitForSingleObject(mutex, INFINITE);

  if (initialised_)
  {
    ::ReleaseMutex(mutex);
    ::CloseHandle(mutex);
    return 0;
  }

#if defined(__MINGW32__)
# if defined(UNDER_CE)
  ::InitializeCriticalSection(&crit_section_);
# else
  if (!::InitializeCriticalSectionAndSpinCount(&crit_section_, 0x80000000))
  {
    last_error = ::GetLastError();
    ::ReleaseMutex(mutex);
    ::CloseHandle(mutex);
    return last_error;
  }
# endif
#else
  __try
  {
# if defined(UNDER_CE)
    ::InitializeCriticalSection(&crit_section_);
# else
    if (!::InitializeCriticalSectionAndSpinCount(&crit_section_, 0x80000000))
    {
      last_error = ::GetLastError();
      ::ReleaseMutex(mutex);
      ::CloseHandle(mutex);
      return last_error;
    }
# endif
  }
  __except(GetExceptionCode() == STATUS_NO_MEMORY
      ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
  {
    ::ReleaseMutex(mutex);
    ::CloseHandle(mutex);
    return ERROR_OUTOFMEMORY;
  }
#endif

  initialised_ = true;
  ::ReleaseMutex(mutex);
  ::CloseHandle(mutex);
  return 0;
}

}
}

#include "asio/detail/pop_options.hpp"

#endif

#endif
