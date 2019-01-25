
#ifndef ASIO_WINDOWS_OBJECT_HANDLE_HPP
#define ASIO_WINDOWS_OBJECT_HANDLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"

#if defined(ASIO_HAS_WINDOWS_OBJECT_HANDLE) \
  || defined(GENERATING_DOCUMENTATION)

#include "asio/windows/basic_object_handle.hpp"

namespace asio {
namespace windows {

/// Typedef for the typical usage of an object handle.
typedef basic_object_handle<> object_handle;

} // namespace windows
} // namespace asio

#endif // defined(ASIO_HAS_WINDOWS_OBJECT_HANDLE)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // ASIO_WINDOWS_OBJECT_HANDLE_HPP
