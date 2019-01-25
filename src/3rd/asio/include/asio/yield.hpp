
#include "coroutine.hpp"

#ifndef reenter
# define reenter(c) ASIO_CORO_REENTER(c)
#endif

#ifndef yield
# define yield ASIO_CORO_YIELD
#endif

#ifndef fork
# define fork ASIO_CORO_FORK
#endif
