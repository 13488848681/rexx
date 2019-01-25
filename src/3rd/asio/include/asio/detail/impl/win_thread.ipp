
#ifndef ASIO_DETAIL_IMPL_WIN_THREAD_IPP
#define ASIO_DETAIL_IMPL_WIN_THREAD_IPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include "asio/detail/config.hpp"

#if defined(ASIO_WINDOWS) && !defined(UNDER_CE)

#include <process.h>
#include "asio/detail/throw_error.hpp"
#include "asio/detail/win_thread.hpp"
#include "asio/error.hpp"

#include "asio/detail/push_options.hpp"

namespace asio {
namespace detail {

win_thread::~win_thread()
{
  ::CloseHandle(thread_);

}

void win_thread::join()
{
  HANDLE handles[2] = { exit_event_, thread_ };
  ::WaitForMultipleObjects(2, handles, FALSE, INFINITE);
  ::CloseHandle(exit_event_);
  if (terminate_threads())
  {
    ::TerminateThread(thread_, 0);
  }
  else
  {
    ::QueueUserAPC(apc_function, thread_, 0);
    ::WaitForSingleObject(thread_, INFINITE);
  }
}

void win_thread::start_thread(func_base* arg, unsigned int stack_size)
{
  ::HANDLE entry_event = 0;
  arg->entry_event_ = entry_event = ::CreateEvent(0, true, false, 0);
  if (!entry_event)
  {
    DWORD last_error = ::GetLastError();
    delete arg;
    asio::error_code ec(last_error,
        asio::error::get_system_category());
    asio::detail::throw_error(ec, "thread.entry_event");
  }

  arg->exit_event_ = exit_event_ = ::CreateEvent(0, true, false, 0);
  if (!exit_event_)
  {
    DWORD last_error = ::GetLastError();
    delete arg;
    asio::error_code ec(last_error,
        asio::error::get_system_category());
    asio::detail::throw_error(ec, "thread.exit_event");
  }

  unsigned int thread_id = 0;
  thread_ = reinterpret_cast<HANDLE>(::_beginthreadex(0,
        stack_size, win_thread_function, arg, 0, &thread_id));
  if (!thread_)
  {
    DWORD last_error = ::GetLastError();
    delete arg;
    if (entry_event)
      ::CloseHandle(entry_event);
    if (exit_event_)
      ::CloseHandle(exit_event_);
    asio::error_code ec(last_error,
        asio::error::get_system_category());
    asio::detail::throw_error(ec, "thread");
  }

  if (entry_event)
  {
    ::WaitForSingleObject(entry_event, INFINITE);
    ::CloseHandle(entry_event);
  }
}

unsigned int __stdcall win_thread_function(void* arg)
{
  win_thread::auto_func_base_ptr func = {
      static_cast<win_thread::func_base*>(arg) };

  ::SetEvent(func.ptr->entry_event_);

  func.ptr->run();

  HANDLE exit_event = func.ptr->exit_event_;
  delete func.ptr;
  func.ptr = 0;
  ::SetEvent(exit_event);
  ::SleepEx(INFINITE, TRUE);

  return 0;
}

#if defined(WINVER) && (WINVER < 0x0500)
void __stdcall apc_function(ULONG) {}
#else
void __stdcall apc_function(ULONG_PTR) {}
#endif

}
}

#include "asio/detail/pop_options.hpp"

#endif

#endif
