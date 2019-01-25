

#ifndef WEBSOCKETPP_COMMON_THREAD_HPP
#define WEBSOCKETPP_COMMON_THREAD_HPP

#include <websocketpp/common/cpp11.hpp>

// If we autodetect C++11 and haven't been explicitly instructed to not use
// C++11 threads, then set the defines that instructs the rest of this header
// to use C++11 <thread> and <mutex>
#if defined _WEBSOCKETPP_CPP11_INTERNAL_ && !defined _WEBSOCKETPP_NO_CPP11_THREAD_
    // MinGW by default does not support C++11 thread/mutex so even if the
    // internal check for C++11 passes, ignore it if we are on MinGW
    #if (!defined(__MINGW32__) && !defined(__MINGW64__))
        #ifndef _WEBSOCKETPP_CPP11_THREAD_
            #define _WEBSOCKETPP_CPP11_THREAD_
        #endif
    #endif
#endif

#ifdef _WEBSOCKETPP_CPP11_THREAD_
    #include <thread>
    #include <mutex>
    #include <condition_variable>
#else
    #include <boost/thread.hpp>
    #include <boost/thread/mutex.hpp>
    #include <boost/thread/condition_variable.hpp>
#endif

namespace websocketpp {
namespace lib {

#ifdef _WEBSOCKETPP_CPP11_THREAD_
    using std::mutex;
    using std::lock_guard;
    using std::thread;
    using std::unique_lock;
    using std::condition_variable;
#else
    using boost::mutex;
    using boost::lock_guard;
    using boost::thread;
    using boost::unique_lock;
    using boost::condition_variable;
#endif

} // namespace lib
} // namespace websocketpp

#endif // WEBSOCKETPP_COMMON_THREAD_HPP
