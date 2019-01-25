

#ifndef ASIO_DETAIL_ADDRESSOF_HPP
#define ASIO_DETAIL_ADDRESSOF_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include "asio/detail/config.hpp"

#if defined(ASIO_HAS_STD_ADDRESSOF)
# include <memory>
#else
# include <boost/utility/addressof.hpp>
#endif

namespace asio {
namespace detail {

#if defined(ASIO_HAS_STD_ADDRESSOF)
using std::addressof;
#else
using boost::addressof;
#endif

}
}

#endif
