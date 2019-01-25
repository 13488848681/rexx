

#ifndef ASIO_DETAIL_OPERATION_HPP
#define ASIO_DETAIL_OPERATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"

#if defined(ASIO_HAS_IOCP)
# include "asio/detail/win_iocp_operation.hpp"
#else
# include "asio/detail/task_io_service_operation.hpp"
#endif

namespace asio {
namespace detail {

#if defined(ASIO_HAS_IOCP)
typedef win_iocp_operation operation;
#else
typedef task_io_service_operation operation;
#endif

} // namespace detail
} // namespace asio

#endif // ASIO_DETAIL_OPERATION_HPP
