
#ifndef ASIO_BASIC_STREAMBUF_FWD_HPP
#define ASIO_BASIC_STREAMBUF_FWD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"

#if !defined(ASIO_NO_IOSTREAM)

#include <memory>

namespace asio {

template <typename Allocator = std::allocator<char> >
class basic_streambuf;

} // namespace asio

#endif // !defined(ASIO_NO_IOSTREAM)

#endif // ASIO_BASIC_STREAMBUF_FWD_HPP
