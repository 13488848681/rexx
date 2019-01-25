
#ifndef ASIO_HANDLER_ALLOC_HOOK_HPP
#define ASIO_HANDLER_ALLOC_HOOK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"
#include <cstddef>

#include "asio/detail/push_options.hpp"

namespace asio {


ASIO_DECL void* asio_handler_allocate(
    std::size_t size, ...);

/// Default deallocation function for handlers.
/**
 * Implement asio_handler_allocate and asio_handler_deallocate for your own
 * handlers to provide custom allocation for the associated temporary objects.
 *
 * The default implementation of these allocation hooks uses <tt>::operator
 * new</tt> and <tt>::operator delete</tt>.
 *
 * @sa asio_handler_allocate.
 */
ASIO_DECL void asio_handler_deallocate(
    void* pointer, std::size_t size, ...);

} // namespace asio

#include "asio/detail/pop_options.hpp"

#if defined(ASIO_HEADER_ONLY)
# include "asio/impl/handler_alloc_hook.ipp"
#endif // defined(ASIO_HEADER_ONLY)

#endif // ASIO_HANDLER_ALLOC_HOOK_HPP
