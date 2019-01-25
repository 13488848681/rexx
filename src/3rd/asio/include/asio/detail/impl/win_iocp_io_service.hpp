

#ifndef ASIO_DETAIL_IMPL_WIN_IOCP_IO_SERVICE_HPP
#define ASIO_DETAIL_IMPL_WIN_IOCP_IO_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include "asio/detail/config.hpp"

#if defined(ASIO_HAS_IOCP)

#include "asio/detail/addressof.hpp"
#include "asio/detail/completion_handler.hpp"
#include "asio/detail/fenced_block.hpp"
#include "asio/detail/handler_alloc_helpers.hpp"
#include "asio/detail/handler_invoke_helpers.hpp"

#include "asio/detail/push_options.hpp"

namespace asio {
namespace detail {

template <typename Handler>
void win_iocp_io_service::dispatch(Handler& handler)
{
  if (thread_call_stack::contains(this))
  {
    fenced_block b(fenced_block::full);
    asio_handler_invoke_helpers::invoke(handler, handler);
  }
  else
  {
    typedef completion_handler<Handler> op;
    typename op::ptr p = { asio::detail::addressof(handler),
      asio_handler_alloc_helpers::allocate(
        sizeof(op), handler), 0 };
    p.p = new (p.v) op(handler);

    ASIO_HANDLER_CREATION((p.p, "io_service", this, "dispatch"));

    post_immediate_completion(p.p, false);
    p.v = p.p = 0;
  }
}

template <typename Handler>
void win_iocp_io_service::post(Handler& handler)
{
  typedef completion_handler<Handler> op;
  typename op::ptr p = { asio::detail::addressof(handler),
    asio_handler_alloc_helpers::allocate(
      sizeof(op), handler), 0 };
  p.p = new (p.v) op(handler);

  ASIO_HANDLER_CREATION((p.p, "io_service", this, "post"));

  post_immediate_completion(p.p, false);
  p.v = p.p = 0;
}

template <typename Time_Traits>
void win_iocp_io_service::add_timer_queue(
    timer_queue<Time_Traits>& queue)
{
  do_add_timer_queue(queue);
}

template <typename Time_Traits>
void win_iocp_io_service::remove_timer_queue(
    timer_queue<Time_Traits>& queue)
{
  do_remove_timer_queue(queue);
}

template <typename Time_Traits>
void win_iocp_io_service::schedule_timer(timer_queue<Time_Traits>& queue,
    const typename Time_Traits::time_type& time,
    typename timer_queue<Time_Traits>::per_timer_data& timer, wait_op* op)
{
  if (::InterlockedExchangeAdd(&shutdown_, 0) != 0)
  {
    post_immediate_completion(op, false);
    return;
  }

  mutex::scoped_lock lock(dispatch_mutex_);

  bool earliest = queue.enqueue_timer(time, timer, op);
  work_started();
  if (earliest)
    update_timeout();
}

template <typename Time_Traits>
std::size_t win_iocp_io_service::cancel_timer(timer_queue<Time_Traits>& queue,
    typename timer_queue<Time_Traits>::per_timer_data& timer,
    std::size_t max_cancelled)
{
  if (::InterlockedExchangeAdd(&shutdown_, 0) != 0)
    return 0;

  mutex::scoped_lock lock(dispatch_mutex_);
  op_queue<win_iocp_operation> ops;
  std::size_t n = queue.cancel_timer(timer, ops, max_cancelled);
  post_deferred_completions(ops);
  return n;
}

}
}

#include "asio/detail/pop_options.hpp"

#endif

#endif
