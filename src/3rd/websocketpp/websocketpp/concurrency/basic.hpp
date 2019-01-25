
#ifndef WEBSOCKETPP_CONCURRENCY_BASIC_HPP
#define WEBSOCKETPP_CONCURRENCY_BASIC_HPP

#include <websocketpp/common/thread.hpp>

namespace websocketpp {
namespace concurrency {

/// Concurrency policy that uses std::mutex / boost::mutex
class basic {
public:
    typedef lib::mutex mutex_type;
    typedef lib::lock_guard<mutex_type> scoped_lock_type;
};

} // namespace concurrency
} // namespace websocketpp

#endif // WEBSOCKETPP_CONCURRENCY_BASIC_HPP
