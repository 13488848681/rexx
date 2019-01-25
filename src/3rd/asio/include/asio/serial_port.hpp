
#ifndef ASIO_SERIAL_PORT_HPP
#define ASIO_SERIAL_PORT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"

#if defined(ASIO_HAS_SERIAL_PORT) \
  || defined(GENERATING_DOCUMENTATION)

#include "asio/basic_serial_port.hpp"

namespace asio {

/// Typedef for the typical usage of a serial port.
typedef basic_serial_port<> serial_port;

} // namespace asio

#endif // defined(ASIO_HAS_SERIAL_PORT)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // ASIO_SERIAL_PORT_HPP
