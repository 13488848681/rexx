
#ifndef ASIO_DETAIL_TASK_IO_SERVICE_THREAD_INFO_HPP
#define ASIO_DETAIL_TASK_IO_SERVICE_THREAD_INFO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/op_queue.hpp"
#include "asio/detail/thread_info_base.hpp"

#include "asio/detail/push_options.hpp"

namespace asio {
namespace detail {

class task_io_service;
class task_io_service_operation;

struct task_io_service_thread_info : public thread_info_base
{
  op_queue<task_io_service_operation> private_op_queue;
  long private_outstanding_work;
};

} // namespace detail
} // namespace asio

#include "asio/detail/pop_options.hpp"

#endif // ASIO_DETAIL_TASK_IO_SERVICE_THREAD_INFO_HPP
