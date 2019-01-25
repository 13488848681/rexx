
#ifndef ASIO_SIGNAL_SET_HPP
#define ASIO_SIGNAL_SET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"
#include "asio/basic_signal_set.hpp"

namespace asio {

/// Typedef for the typical usage of a signal set.
typedef basic_signal_set<> signal_set;

} // namespace asio

#endif // ASIO_SIGNAL_SET_HPP
