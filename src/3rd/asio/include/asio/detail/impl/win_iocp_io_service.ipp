
#ifndef ASIO_DETAIL_IMPL_WIN_IOCP_IO_SERVICE_IPP
#define ASIO_DETAIL_IMPL_WIN_IOCP_IO_SERVICE_IPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include "asio/detail/config.hpp"

#if defined(ASIO_HAS_IOCP)

#include "asio/error.hpp"
#include "asio/io_service.hpp"
#include "asio/detail/cstdint.hpp"
#include "asio/detail/handler_alloc_helpers.hpp"
#include "asio/detail/handler_invoke_helpers.hpp"
#include "asio/detail/limits.hpp"
#include "asio/detail/throw_error.hpp"
#include "asio/detail/win_iocp_io_service.hpp"

#include "asio/detail/push_options.hpp"

namespace asio {
namespace detail {

struct win_iocp_io_service::work_finished_on_block_exit
{
  ~work_finished_on_block_exit()
  {
    io_service_->work_finished();
  }

  win_iocp_io_service* io_service_;
};

struct win_iocp_io_service::timer_thread_function
{
  void operator()()
  {
    while (::InterlockedExchangeAdd(&io_service_->shutdown_, 0) == 0)
    {
      if (::WaitForSingleObject(io_service_->waitable_timer_.handle,
            INFINITE) == WAIT_OBJECT_0)
      {
        ::InterlockedExchange(&io_service_->dispatch_required_, 1);
        ::PostQueuedCompletionStatus(io_service_->iocp_.handle,
            0, wake_for_dispatch, 0);
      }
    }
  }

  win_iocp_io_service* io_service_;
};

win_iocp_io_service::win_iocp_io_service(
    asio::io_service& io_service, size_t concurrency_hint)
  : asio::detail::service_base<win_iocp_io_service>(io_service),
    iocp_(),
    outstanding_work_(0),
    stopped_(0),
    stop_event_posted_(0),
    shutdown_(0),
    gqcs_timeout_(get_gqcs_timeout()),
    dispatch_required_(0)
{
  ASIO_HANDLER_TRACKING_INIT;

  iocp_.handle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0,
      static_cast<DWORD>(concurrency_hint < DWORD(~0)
        ? concurrency_hint : DWORD(~0)));
  if (!iocp_.handle)
  {
    DWORD last_error = ::GetLastError();
    asio::error_code ec(last_error,
        asio::error::get_system_category());
    asio::detail::throw_error(ec, "iocp");
  }
}

void win_iocp_io_service::shutdown_service()
{
  ::InterlockedExchange(&shutdown_, 1);

  if (timer_thread_.get())
  {
    LARGE_INTEGER timeout;
    timeout.QuadPart = 1;
    ::SetWaitableTimer(waitable_timer_.handle, &timeout, 1, 0, 0, FALSE);
  }

  while (::InterlockedExchangeAdd(&outstanding_work_, 0) > 0)
  {
    op_queue<win_iocp_operation> ops;
    timer_queues_.get_all_timers(ops);
    ops.push(completed_ops_);
    if (!ops.empty())
    {
      while (win_iocp_operation* op = ops.front())
      {
        ops.pop();
        ::InterlockedDecrement(&outstanding_work_);
        op->destroy();
      }
    }
    else
    {
      DWORD bytes_transferred = 0;
      dword_ptr_t completion_key = 0;
      LPOVERLAPPED overlapped = 0;
      ::GetQueuedCompletionStatus(iocp_.handle, &bytes_transferred,
          &completion_key, &overlapped, gqcs_timeout_);
      if (overlapped)
      {
        ::InterlockedDecrement(&outstanding_work_);
        static_cast<win_iocp_operation*>(overlapped)->destroy();
      }
    }
  }

  if (timer_thread_.get())
    timer_thread_->join();
}

asio::error_code win_iocp_io_service::register_handle(
    HANDLE handle, asio::error_code& ec)
{
  if (::CreateIoCompletionPort(handle, iocp_.handle, 0, 0) == 0)
  {
    DWORD last_error = ::GetLastError();
    ec = asio::error_code(last_error,
        asio::error::get_system_category());
  }
  else
  {
    ec = asio::error_code();
  }
  return ec;
}

size_t win_iocp_io_service::run(asio::error_code& ec)
{
  if (::InterlockedExchangeAdd(&outstanding_work_, 0) == 0)
  {
    stop();
    ec = asio::error_code();
    return 0;
  }

  win_iocp_thread_info this_thread;
  thread_call_stack::context ctx(this, this_thread);

  size_t n = 0;
  while (do_one(true, ec))
    if (n != (std::numeric_limits<size_t>::max)())
      ++n;
  return n;
}

size_t win_iocp_io_service::run_one(asio::error_code& ec)
{
  if (::InterlockedExchangeAdd(&outstanding_work_, 0) == 0)
  {
    stop();
    ec = asio::error_code();
    return 0;
  }

  win_iocp_thread_info this_thread;
  thread_call_stack::context ctx(this, this_thread);

  return do_one(true, ec);
}

size_t win_iocp_io_service::poll(asio::error_code& ec)
{
  if (::InterlockedExchangeAdd(&outstanding_work_, 0) == 0)
  {
    stop();
    ec = asio::error_code();
    return 0;
  }

  win_iocp_thread_info this_thread;
  thread_call_stack::context ctx(this, this_thread);

  size_t n = 0;
  while (do_one(false, ec))
    if (n != (std::numeric_limits<size_t>::max)())
      ++n;
  return n;
}

size_t win_iocp_io_service::poll_one(asio::error_code& ec)
{
  if (::InterlockedExchangeAdd(&outstanding_work_, 0) == 0)
  {
    stop();
    ec = asio::error_code();
    return 0;
  }

  win_iocp_thread_info this_thread;
  thread_call_stack::context ctx(this, this_thread);

  return do_one(false, ec);
}

void win_iocp_io_service::stop()
{
  if (::InterlockedExchange(&stopped_, 1) == 0)
  {
    if (::InterlockedExchange(&stop_event_posted_, 1) == 0)
    {
      if (!::PostQueuedCompletionStatus(iocp_.handle, 0, 0, 0))
      {
        DWORD last_error = ::GetLastError();
        asio::error_code ec(last_error,
            asio::error::get_system_category());
        asio::detail::throw_error(ec, "pqcs");
      }
    }
  }
}

void win_iocp_io_service::post_deferred_completion(win_iocp_operation* op)
{
  op->ready_ = 1;

  if (!::PostQueuedCompletionStatus(iocp_.handle, 0, 0, op))
  {
    mutex::scoped_lock lock(dispatch_mutex_);
    completed_ops_.push(op);
    ::InterlockedExchange(&dispatch_required_, 1);
  }
}

void win_iocp_io_service::post_deferred_completions(
    op_queue<win_iocp_operation>& ops)
{
  while (win_iocp_operation* op = ops.front())
  {
    ops.pop();

    op->ready_ = 1;

    if (!::PostQueuedCompletionStatus(iocp_.handle, 0, 0, op))
    {
      mutex::scoped_lock lock(dispatch_mutex_);
      completed_ops_.push(op);
      completed_ops_.push(ops);
      ::InterlockedExchange(&dispatch_required_, 1);
    }
  }
}

void win_iocp_io_service::abandon_operations(
    op_queue<win_iocp_operation>& ops)
{
  while (win_iocp_operation* op = ops.front())
  {
    ops.pop();
    ::InterlockedDecrement(&outstanding_work_);
    op->destroy();
  }
}

void win_iocp_io_service::on_pending(win_iocp_operation* op)
{
  if (::InterlockedCompareExchange(&op->ready_, 1, 0) == 1)
  {
    if (!::PostQueuedCompletionStatus(iocp_.handle,
          0, overlapped_contains_result, op))
    {
      mutex::scoped_lock lock(dispatch_mutex_);
      completed_ops_.push(op);
      ::InterlockedExchange(&dispatch_required_, 1);
    }
  }
}

void win_iocp_io_service::on_completion(win_iocp_operation* op,
    DWORD last_error, DWORD bytes_transferred)
{
  op->ready_ = 1;

  op->Internal = reinterpret_cast<ulong_ptr_t>(
      &asio::error::get_system_category());
  op->Offset = last_error;
  op->OffsetHigh = bytes_transferred;

  if (!::PostQueuedCompletionStatus(iocp_.handle,
        0, overlapped_contains_result, op))
  {
    mutex::scoped_lock lock(dispatch_mutex_);
    completed_ops_.push(op);
    ::InterlockedExchange(&dispatch_required_, 1);
  }
}

void win_iocp_io_service::on_completion(win_iocp_operation* op,
    const asio::error_code& ec, DWORD bytes_transferred)
{
  op->ready_ = 1;

  op->Internal = reinterpret_cast<ulong_ptr_t>(&ec.category());
  op->Offset = ec.value();
  op->OffsetHigh = bytes_transferred;

  if (!::PostQueuedCompletionStatus(iocp_.handle,
        0, overlapped_contains_result, op))
  {
    mutex::scoped_lock lock(dispatch_mutex_);
    completed_ops_.push(op);
    ::InterlockedExchange(&dispatch_required_, 1);
  }
}

size_t win_iocp_io_service::do_one(bool block, asio::error_code& ec)
{
  for (;;)
  {
    if (::InterlockedCompareExchange(&dispatch_required_, 0, 1) == 1)
    {
      mutex::scoped_lock lock(dispatch_mutex_);

      op_queue<win_iocp_operation> ops;
      ops.push(completed_ops_);
      timer_queues_.get_ready_timers(ops);
      post_deferred_completions(ops);
      update_timeout();
    }

    DWORD bytes_transferred = 0;
    dword_ptr_t completion_key = 0;
    LPOVERLAPPED overlapped = 0;
    ::SetLastError(0);
    BOOL ok = ::GetQueuedCompletionStatus(iocp_.handle, &bytes_transferred,
        &completion_key, &overlapped, block ? gqcs_timeout_ : 0);
    DWORD last_error = ::GetLastError();

    if (overlapped)
    {
      win_iocp_operation* op = static_cast<win_iocp_operation*>(overlapped);
      asio::error_code result_ec(last_error,
          asio::error::get_system_category());

      if (completion_key == overlapped_contains_result)
      {
        result_ec = asio::error_code(static_cast<int>(op->Offset),
            *reinterpret_cast<asio::error_category*>(op->Internal));
        bytes_transferred = op->OffsetHigh;
      }

      else
      {
        op->Internal = reinterpret_cast<ulong_ptr_t>(&result_ec.category());
        op->Offset = result_ec.value();
        op->OffsetHigh = bytes_transferred;
      }

      if (::InterlockedCompareExchange(&op->ready_, 1, 0) == 1)
      {
        work_finished_on_block_exit on_exit = { this };
        (void)on_exit;

        op->complete(*this, result_ec, bytes_transferred);
        ec = asio::error_code();
        return 1;
      }
    }
    else if (!ok)
    {
      if (last_error != WAIT_TIMEOUT)
      {
        ec = asio::error_code(last_error,
            asio::error::get_system_category());
        return 0;
      }

      if (block)
        continue;

      ec = asio::error_code();
      return 0;
    }
    else if (completion_key == wake_for_dispatch)
    {

    }
    else
    {
      ::InterlockedExchange(&stop_event_posted_, 0);

      if (::InterlockedExchangeAdd(&stopped_, 0) != 0)
      {
        if (::InterlockedExchange(&stop_event_posted_, 1) == 0)
        {
          if (!::PostQueuedCompletionStatus(iocp_.handle, 0, 0, 0))
          {
            last_error = ::GetLastError();
            ec = asio::error_code(last_error,
                asio::error::get_system_category());
            return 0;
          }
        }

        ec = asio::error_code();
        return 0;
      }
    }
  }
}

DWORD win_iocp_io_service::get_gqcs_timeout()
{
  OSVERSIONINFOEX osvi;
  ZeroMemory(&osvi, sizeof(osvi));
  osvi.dwOSVersionInfoSize = sizeof(osvi);
  osvi.dwMajorVersion = 6ul;

  const uint64_t condition_mask = ::VerSetConditionMask(
      0, VER_MAJORVERSION, VER_GREATER_EQUAL);

  if (!!::VerifyVersionInfo(&osvi, VER_MAJORVERSION, condition_mask))
    return INFINITE;

  return default_gqcs_timeout;
}

void win_iocp_io_service::do_add_timer_queue(timer_queue_base& queue)
{
  mutex::scoped_lock lock(dispatch_mutex_);

  timer_queues_.insert(&queue);

  if (!waitable_timer_.handle)
  {
    waitable_timer_.handle = ::CreateWaitableTimer(0, FALSE, 0);
    if (waitable_timer_.handle == 0)
    {
      DWORD last_error = ::GetLastError();
      asio::error_code ec(last_error,
          asio::error::get_system_category());
      asio::detail::throw_error(ec, "timer");
    }

    LARGE_INTEGER timeout;
    timeout.QuadPart = -max_timeout_usec;
    timeout.QuadPart *= 10;
    ::SetWaitableTimer(waitable_timer_.handle,
        &timeout, max_timeout_msec, 0, 0, FALSE);
  }

  if (!timer_thread_.get())
  {
    timer_thread_function thread_function = { this };
    timer_thread_.reset(new thread(thread_function, 65536));
  }
}

void win_iocp_io_service::do_remove_timer_queue(timer_queue_base& queue)
{
  mutex::scoped_lock lock(dispatch_mutex_);

  timer_queues_.erase(&queue);
}

void win_iocp_io_service::update_timeout()
{
  if (timer_thread_.get())
  {
    long timeout_usec = timer_queues_.wait_duration_usec(max_timeout_usec);
    if (timeout_usec < max_timeout_usec)
    {
      LARGE_INTEGER timeout;
      timeout.QuadPart = -timeout_usec;
      timeout.QuadPart *= 10;
      ::SetWaitableTimer(waitable_timer_.handle,
          &timeout, max_timeout_msec, 0, 0, FALSE);
    }
  }
}

}
}

#include "asio/detail/pop_options.hpp"

#endif

#endif
