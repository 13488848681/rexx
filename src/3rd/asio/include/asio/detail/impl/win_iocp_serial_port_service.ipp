
#ifndef ASIO_DETAIL_IMPL_WIN_IOCP_SERIAL_PORT_SERVICE_IPP
#define ASIO_DETAIL_IMPL_WIN_IOCP_SERIAL_PORT_SERVICE_IPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include "asio/detail/config.hpp"

#if defined(ASIO_HAS_IOCP) && defined(ASIO_HAS_SERIAL_PORT)

#include <cstring>
#include "asio/detail/win_iocp_serial_port_service.hpp"

#include "asio/detail/push_options.hpp"

namespace asio {
namespace detail {

win_iocp_serial_port_service::win_iocp_serial_port_service(
    asio::io_service& io_service)
  : handle_service_(io_service)
{
}

void win_iocp_serial_port_service::shutdown_service()
{
}

asio::error_code win_iocp_serial_port_service::open(
    win_iocp_serial_port_service::implementation_type& impl,
    const std::string& device, asio::error_code& ec)
{
  if (is_open(impl))
  {
    ec = asio::error::already_open;
    return ec;
  }

  std::string name = (device[0] == '\\') ? device : "\\\\.\\" + device;

  ::HANDLE handle = ::CreateFileA(name.c_str(),
      GENERIC_READ | GENERIC_WRITE, 0, 0,
      OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);
  if (handle == INVALID_HANDLE_VALUE)
  {
    DWORD last_error = ::GetLastError();
    ec = asio::error_code(last_error,
        asio::error::get_system_category());
    return ec;
  }

  using namespace std;
  ::DCB dcb;
  memset(&dcb, 0, sizeof(DCB));
  dcb.DCBlength = sizeof(DCB);
  if (!::GetCommState(handle, &dcb))
  {
    DWORD last_error = ::GetLastError();
    ::CloseHandle(handle);
    ec = asio::error_code(last_error,
        asio::error::get_system_category());
    return ec;
  }

  dcb.fBinary = TRUE;
  dcb.fDsrSensitivity = FALSE;
  dcb.fNull = FALSE;
  dcb.fAbortOnError = FALSE;
  if (!::SetCommState(handle, &dcb))
  {
    DWORD last_error = ::GetLastError();
    ::CloseHandle(handle);
    ec = asio::error_code(last_error,
        asio::error::get_system_category());
    return ec;
  }

  ::COMMTIMEOUTS timeouts;
  timeouts.ReadIntervalTimeout = 1;
  timeouts.ReadTotalTimeoutMultiplier = 0;
  timeouts.ReadTotalTimeoutConstant = 0;
  timeouts.WriteTotalTimeoutMultiplier = 0;
  timeouts.WriteTotalTimeoutConstant = 0;
  if (!::SetCommTimeouts(handle, &timeouts))
  {
    DWORD last_error = ::GetLastError();
    ::CloseHandle(handle);
    ec = asio::error_code(last_error,
        asio::error::get_system_category());
    return ec;
  }

  if (handle_service_.assign(impl, handle, ec))
    ::CloseHandle(handle);
  return ec;
}

asio::error_code win_iocp_serial_port_service::do_set_option(
    win_iocp_serial_port_service::implementation_type& impl,
    win_iocp_serial_port_service::store_function_type store,
    const void* option, asio::error_code& ec)
{
  using namespace std;

  ::DCB dcb;
  memset(&dcb, 0, sizeof(DCB));
  dcb.DCBlength = sizeof(DCB);
  if (!::GetCommState(handle_service_.native_handle(impl), &dcb))
  {
    DWORD last_error = ::GetLastError();
    ec = asio::error_code(last_error,
        asio::error::get_system_category());
    return ec;
  }

  if (store(option, dcb, ec))
    return ec;

  if (!::SetCommState(handle_service_.native_handle(impl), &dcb))
  {
    DWORD last_error = ::GetLastError();
    ec = asio::error_code(last_error,
        asio::error::get_system_category());
    return ec;
  }

  ec = asio::error_code();
  return ec;
}

asio::error_code win_iocp_serial_port_service::do_get_option(
    const win_iocp_serial_port_service::implementation_type& impl,
    win_iocp_serial_port_service::load_function_type load,
    void* option, asio::error_code& ec) const
{
  using namespace std;

  ::DCB dcb;
  memset(&dcb, 0, sizeof(DCB));
  dcb.DCBlength = sizeof(DCB);
  if (!::GetCommState(handle_service_.native_handle(impl), &dcb))
  {
    DWORD last_error = ::GetLastError();
    ec = asio::error_code(last_error,
        asio::error::get_system_category());
    return ec;
  }

  return load(option, dcb, ec);
}

}
}

#include "asio/detail/pop_options.hpp"

#endif

#endif
