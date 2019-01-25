
#ifndef ASIO_DETAIL_IMPL_KQUEUE_REACTOR_IPP
#define ASIO_DETAIL_IMPL_KQUEUE_REACTOR_IPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include "asio/detail/config.hpp"

#if defined(ASIO_HAS_KQUEUE)

#include "asio/detail/kqueue_reactor.hpp"
#include "asio/detail/throw_error.hpp"
#include "asio/error.hpp"

#include "asio/detail/push_options.hpp"

#if defined(__NetBSD__)
# define ASIO_KQUEUE_EV_SET(ev, ident, filt, flags, fflags, data, udata) \
    EV_SET(ev, ident, filt, flags, fflags, data, \
      reinterpret_cast<intptr_t>(static_cast<void*>(udata)))
#else
# define ASIO_KQUEUE_EV_SET(ev, ident, filt, flags, fflags, data, udata) \
    EV_SET(ev, ident, filt, flags, fflags, data, udata)
#endif

namespace asio {
namespace detail {

kqueue_reactor::kqueue_reactor(asio::io_service& io_service)
  : asio::detail::service_base<kqueue_reactor>(io_service),
    io_service_(use_service<io_service_impl>(io_service)),
    mutex_(),
    kqueue_fd_(do_kqueue_create()),
    interrupter_(),
    shutdown_(false)
{
  struct kevent events[1];
  ASIO_KQUEUE_EV_SET(&events[0], interrupter_.read_descriptor(),
      EVFILT_READ, EV_ADD, 0, 0, &interrupter_);
  if (::kevent(kqueue_fd_, events, 1, 0, 0, 0) == -1)
  {
    asio::error_code error(errno,
        asio::error::get_system_category());
    asio::detail::throw_error(error);
  }
}

kqueue_reactor::~kqueue_reactor()
{
  close(kqueue_fd_);
}

void kqueue_reactor::shutdown_service()
{
  mutex::scoped_lock lock(mutex_);
  shutdown_ = true;
  lock.unlock();

  op_queue<operation> ops;

  while (descriptor_state* state = registered_descriptors_.first())
  {
    for (int i = 0; i < max_ops; ++i)
      ops.push(state->op_queue_[i]);
    state->shutdown_ = true;
    registered_descriptors_.free(state);
  }

  timer_queues_.get_all_timers(ops);

  io_service_.abandon_operations(ops);
}

void kqueue_reactor::fork_service(asio::io_service::fork_event fork_ev)
{
  if (fork_ev == asio::io_service::fork_child)
  {
    kqueue_fd_ = -1;
    kqueue_fd_ = do_kqueue_create();

    interrupter_.recreate();

    struct kevent events[2];
    ASIO_KQUEUE_EV_SET(&events[0], interrupter_.read_descriptor(),
        EVFILT_READ, EV_ADD, 0, 0, &interrupter_);
    if (::kevent(kqueue_fd_, events, 1, 0, 0, 0) == -1)
    {
      asio::error_code ec(errno,
          asio::error::get_system_category());
      asio::detail::throw_error(ec, "kqueue interrupter registration");
    }

    mutex::scoped_lock descriptors_lock(registered_descriptors_mutex_);
    for (descriptor_state* state = registered_descriptors_.first();
        state != 0; state = state->next_)
    {
      if (state->num_kevents_ > 0)
      {
        ASIO_KQUEUE_EV_SET(&events[0], state->descriptor_,
            EVFILT_READ, EV_ADD | EV_CLEAR, 0, 0, state);
        ASIO_KQUEUE_EV_SET(&events[1], state->descriptor_,
            EVFILT_WRITE, EV_ADD | EV_CLEAR, 0, 0, state);
        if (::kevent(kqueue_fd_, events, state->num_kevents_, 0, 0, 0) == -1)
        {
          asio::error_code ec(errno,
              asio::error::get_system_category());
          asio::detail::throw_error(ec, "kqueue re-registration");
        }
      }
    }
  }
}

void kqueue_reactor::init_task()
{
  io_service_.init_task();
}

int kqueue_reactor::register_descriptor(socket_type descriptor,
    kqueue_reactor::per_descriptor_data& descriptor_data)
{
  descriptor_data = allocate_descriptor_state();

  mutex::scoped_lock lock(descriptor_data->mutex_);

  descriptor_data->descriptor_ = descriptor;
  descriptor_data->num_kevents_ = 0;
  descriptor_data->shutdown_ = false;

  return 0;
}

int kqueue_reactor::register_internal_descriptor(
    int op_type, socket_type descriptor,
    kqueue_reactor::per_descriptor_data& descriptor_data, reactor_op* op)
{
  descriptor_data = allocate_descriptor_state();

  mutex::scoped_lock lock(descriptor_data->mutex_);

  descriptor_data->descriptor_ = descriptor;
  descriptor_data->num_kevents_ = 1;
  descriptor_data->shutdown_ = false;
  descriptor_data->op_queue_[op_type].push(op);

  struct kevent events[1];
  ASIO_KQUEUE_EV_SET(&events[0], descriptor, EVFILT_READ,
      EV_ADD | EV_CLEAR, 0, 0, descriptor_data);
  if (::kevent(kqueue_fd_, events, 1, 0, 0, 0) == -1)
    return errno;

  return 0;
}

void kqueue_reactor::move_descriptor(socket_type,
    kqueue_reactor::per_descriptor_data& target_descriptor_data,
    kqueue_reactor::per_descriptor_data& source_descriptor_data)
{
  target_descriptor_data = source_descriptor_data;
  source_descriptor_data = 0;
}

void kqueue_reactor::start_op(int op_type, socket_type descriptor,
    kqueue_reactor::per_descriptor_data& descriptor_data, reactor_op* op,
    bool is_continuation, bool allow_speculative)
{
  if (!descriptor_data)
  {
    op->ec_ = asio::error::bad_descriptor;
    post_immediate_completion(op, is_continuation);
    return;
  }

  mutex::scoped_lock descriptor_lock(descriptor_data->mutex_);

  if (descriptor_data->shutdown_)
  {
    post_immediate_completion(op, is_continuation);
    return;
  }

  if (descriptor_data->op_queue_[op_type].empty())
  {
    static const int num_kevents[max_ops] = { 1, 2, 1 };

    if (allow_speculative
        && (op_type != read_op
          || descriptor_data->op_queue_[except_op].empty()))
    {
      if (op->perform())
      {
        descriptor_lock.unlock();
        io_service_.post_immediate_completion(op, is_continuation);
        return;
      }

      if (descriptor_data->num_kevents_ < num_kevents[op_type])
      {
        struct kevent events[2];
        ASIO_KQUEUE_EV_SET(&events[0], descriptor, EVFILT_READ,
            EV_ADD | EV_CLEAR, 0, 0, descriptor_data);
        ASIO_KQUEUE_EV_SET(&events[1], descriptor, EVFILT_WRITE,
            EV_ADD | EV_CLEAR, 0, 0, descriptor_data);
        if (::kevent(kqueue_fd_, events, num_kevents[op_type], 0, 0, 0) != -1)
        {
          descriptor_data->num_kevents_ = num_kevents[op_type];
        }
        else
        {
          op->ec_ = asio::error_code(errno,
              asio::error::get_system_category());
          io_service_.post_immediate_completion(op, is_continuation);
          return;
        }
      }
    }
    else
    {
      if (descriptor_data->num_kevents_ < num_kevents[op_type])
        descriptor_data->num_kevents_ = num_kevents[op_type];

      struct kevent events[2];
      ASIO_KQUEUE_EV_SET(&events[0], descriptor, EVFILT_READ,
          EV_ADD | EV_CLEAR, 0, 0, descriptor_data);
      ASIO_KQUEUE_EV_SET(&events[1], descriptor, EVFILT_WRITE,
          EV_ADD | EV_CLEAR, 0, 0, descriptor_data);
      ::kevent(kqueue_fd_, events, descriptor_data->num_kevents_, 0, 0, 0);
    }
  }

  descriptor_data->op_queue_[op_type].push(op);
  io_service_.work_started();
}

void kqueue_reactor::cancel_ops(socket_type,
    kqueue_reactor::per_descriptor_data& descriptor_data)
{
  if (!descriptor_data)
    return;

  mutex::scoped_lock descriptor_lock(descriptor_data->mutex_);

  op_queue<operation> ops;
  for (int i = 0; i < max_ops; ++i)
  {
    while (reactor_op* op = descriptor_data->op_queue_[i].front())
    {
      op->ec_ = asio::error::operation_aborted;
      descriptor_data->op_queue_[i].pop();
      ops.push(op);
    }
  }

  descriptor_lock.unlock();

  io_service_.post_deferred_completions(ops);
}

void kqueue_reactor::deregister_descriptor(socket_type descriptor,
    kqueue_reactor::per_descriptor_data& descriptor_data, bool closing)
{
  if (!descriptor_data)
    return;

  mutex::scoped_lock descriptor_lock(descriptor_data->mutex_);

  if (!descriptor_data->shutdown_)
  {
    if (closing)
    {

    }
    else
    {
      struct kevent events[2];
      ASIO_KQUEUE_EV_SET(&events[0], descriptor,
          EVFILT_READ, EV_DELETE, 0, 0, 0);
      ASIO_KQUEUE_EV_SET(&events[1], descriptor,
          EVFILT_WRITE, EV_DELETE, 0, 0, 0);
      ::kevent(kqueue_fd_, events, descriptor_data->num_kevents_, 0, 0, 0);
    }

    op_queue<operation> ops;
    for (int i = 0; i < max_ops; ++i)
    {
      while (reactor_op* op = descriptor_data->op_queue_[i].front())
      {
        op->ec_ = asio::error::operation_aborted;
        descriptor_data->op_queue_[i].pop();
        ops.push(op);
      }
    }

    descriptor_data->descriptor_ = -1;
    descriptor_data->shutdown_ = true;

    descriptor_lock.unlock();

    free_descriptor_state(descriptor_data);
    descriptor_data = 0;

    io_service_.post_deferred_completions(ops);
  }
}

void kqueue_reactor::deregister_internal_descriptor(socket_type descriptor,
    kqueue_reactor::per_descriptor_data& descriptor_data)
{
  if (!descriptor_data)
    return;

  mutex::scoped_lock descriptor_lock(descriptor_data->mutex_);

  if (!descriptor_data->shutdown_)
  {
    struct kevent events[2];
    ASIO_KQUEUE_EV_SET(&events[0], descriptor,
        EVFILT_READ, EV_DELETE, 0, 0, 0);
    ASIO_KQUEUE_EV_SET(&events[1], descriptor,
        EVFILT_WRITE, EV_DELETE, 0, 0, 0);
    ::kevent(kqueue_fd_, events, descriptor_data->num_kevents_, 0, 0, 0);

    op_queue<operation> ops;
    for (int i = 0; i < max_ops; ++i)
      ops.push(descriptor_data->op_queue_[i]);

    descriptor_data->descriptor_ = -1;
    descriptor_data->shutdown_ = true;

    descriptor_lock.unlock();

    free_descriptor_state(descriptor_data);
    descriptor_data = 0;
  }
}

void kqueue_reactor::run(bool block, op_queue<operation>& ops)
{
  mutex::scoped_lock lock(mutex_);

  timespec timeout_buf = { 0, 0 };
  timespec* timeout = block ? get_timeout(timeout_buf) : &timeout_buf;

  lock.unlock();

  struct kevent events[128];
  int num_events = kevent(kqueue_fd_, 0, 0, events, 128, timeout);

  for (int i = 0; i < num_events; ++i)
  {
    void* ptr = reinterpret_cast<void*>(events[i].udata);
    if (ptr == &interrupter_)
    {
      interrupter_.reset();
    }
    else
    {
      descriptor_state* descriptor_data = static_cast<descriptor_state*>(ptr);
      mutex::scoped_lock descriptor_lock(descriptor_data->mutex_);

      if (events[i].filter == EVFILT_WRITE
          && descriptor_data->num_kevents_ == 2
          && descriptor_data->op_queue_[write_op].empty())
      {
        struct kevent delete_events[1];
        ASIO_KQUEUE_EV_SET(&delete_events[0],
            descriptor_data->descriptor_, EVFILT_WRITE, EV_DELETE, 0, 0, 0);
        ::kevent(kqueue_fd_, delete_events, 1, 0, 0, 0);
        descriptor_data->num_kevents_ = 1;
      }

#if defined(__NetBSD__)
      static const unsigned int filter[max_ops] =
#else
      static const int filter[max_ops] =
#endif
        { EVFILT_READ, EVFILT_WRITE, EVFILT_READ };
      for (int j = max_ops - 1; j >= 0; --j)
      {
        if (events[i].filter == filter[j])
        {
          if (j != except_op || events[i].flags & EV_OOBAND)
          {
            while (reactor_op* op = descriptor_data->op_queue_[j].front())
            {
              if (events[i].flags & EV_ERROR)
              {
                op->ec_ = asio::error_code(
                    static_cast<int>(events[i].data),
                    asio::error::get_system_category());
                descriptor_data->op_queue_[j].pop();
                ops.push(op);
              }
              if (op->perform())
              {
                descriptor_data->op_queue_[j].pop();
                ops.push(op);
              }
              else
                break;
            }
          }
        }
      }
    }
  }

  lock.lock();
  timer_queues_.get_ready_timers(ops);
}

void kqueue_reactor::interrupt()
{
  interrupter_.interrupt();
}

int kqueue_reactor::do_kqueue_create()
{
  int fd = ::kqueue();
  if (fd == -1)
  {
    asio::error_code ec(errno,
        asio::error::get_system_category());
    asio::detail::throw_error(ec, "kqueue");
  }
  return fd;
}

kqueue_reactor::descriptor_state* kqueue_reactor::allocate_descriptor_state()
{
  mutex::scoped_lock descriptors_lock(registered_descriptors_mutex_);
  return registered_descriptors_.alloc();
}

void kqueue_reactor::free_descriptor_state(kqueue_reactor::descriptor_state* s)
{
  mutex::scoped_lock descriptors_lock(registered_descriptors_mutex_);
  registered_descriptors_.free(s);
}

void kqueue_reactor::do_add_timer_queue(timer_queue_base& queue)
{
  mutex::scoped_lock lock(mutex_);
  timer_queues_.insert(&queue);
}

void kqueue_reactor::do_remove_timer_queue(timer_queue_base& queue)
{
  mutex::scoped_lock lock(mutex_);
  timer_queues_.erase(&queue);
}

timespec* kqueue_reactor::get_timeout(timespec& ts)
{
  long usec = timer_queues_.wait_duration_usec(5 * 60 * 1000 * 1000);
  ts.tv_sec = usec / 1000000;
  ts.tv_nsec = (usec % 1000000) * 1000;
  return &ts;
}

}
}

#undef ASIO_KQUEUE_EV_SET

#include "asio/detail/pop_options.hpp"

#endif

#endif