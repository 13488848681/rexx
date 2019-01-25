

#ifndef WEBSOCKETPP_COMMON_CHRONO_HPP
#define WEBSOCKETPP_COMMON_CHRONO_HPP

#include <websocketpp/common/cpp11.hpp>

#if defined _WEBSOCKETPP_CPP11_INTERNAL_ && !defined _WEBSOCKETPP_NO_CPP11_CHRONO_
    #ifndef _WEBSOCKETPP_CPP11_CHRONO_
        #define _WEBSOCKETPP_CPP11_CHRONO_
    #endif
#endif

#ifdef _WEBSOCKETPP_CPP11_CHRONO_
    #include <chrono>
#else
    #include <boost/chrono.hpp>
#endif

namespace websocketpp {
namespace lib {

#ifdef _WEBSOCKETPP_CPP11_CHRONO_
    namespace chrono = std::chrono;
#else
    namespace chrono = boost::chrono;
#endif

} // namespace lib
} // namespace websocketpp

#endif // WEBSOCKETPP_COMMON_CHRONO_HPP
