
#ifndef ASIO_DETAIL_SHARED_PTR_HPP
#define ASIO_DETAIL_SHARED_PTR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"

#if defined(ASIO_HAS_STD_SHARED_PTR)
# include <memory>
#else // defined(ASIO_HAS_STD_SHARED_PTR)
# include <boost/shared_ptr.hpp>
#endif // defined(ASIO_HAS_STD_SHARED_PTR)

namespace asio {
namespace detail {

#if defined(ASIO_HAS_STD_SHARED_PTR)
using std::shared_ptr;
#else // defined(ASIO_HAS_STD_SHARED_PTR)
using boost::shared_ptr;
#endif // defined(ASIO_HAS_STD_SHARED_PTR)

} // namespace detail
} // namespace asio

#endif // ASIO_DETAIL_SHARED_PTR_HPP
