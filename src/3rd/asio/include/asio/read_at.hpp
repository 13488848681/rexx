
#ifndef ASIO_READ_AT_HPP
#define ASIO_READ_AT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"
#include <cstddef>
#include "asio/async_result.hpp"
#include "asio/basic_streambuf_fwd.hpp"
#include "asio/detail/cstdint.hpp"
#include "asio/error.hpp"

#include "asio/detail/push_options.hpp"

namespace asio {

/**
 * @defgroup read_at asio::read_at
 *
 * @brief Attempt to read a certain amount of data at the specified offset
 * before returning.
 */
/*@{*/


template <typename SyncRandomAccessReadDevice, typename MutableBufferSequence>
std::size_t read_at(SyncRandomAccessReadDevice& d,
    uint64_t offset, const MutableBufferSequence& buffers);

template <typename SyncRandomAccessReadDevice, typename MutableBufferSequence>
std::size_t read_at(SyncRandomAccessReadDevice& d,
    uint64_t offset, const MutableBufferSequence& buffers,
    asio::error_code& ec);


template <typename SyncRandomAccessReadDevice, typename MutableBufferSequence,
    typename CompletionCondition>
std::size_t read_at(SyncRandomAccessReadDevice& d,
    uint64_t offset, const MutableBufferSequence& buffers,
    CompletionCondition completion_condition);


template <typename SyncRandomAccessReadDevice, typename MutableBufferSequence,
    typename CompletionCondition>
std::size_t read_at(SyncRandomAccessReadDevice& d,
    uint64_t offset, const MutableBufferSequence& buffers,
    CompletionCondition completion_condition, asio::error_code& ec);

#if !defined(ASIO_NO_IOSTREAM)


template <typename SyncRandomAccessReadDevice, typename Allocator>
std::size_t read_at(SyncRandomAccessReadDevice& d,
    uint64_t offset, basic_streambuf<Allocator>& b);


template <typename SyncRandomAccessReadDevice, typename Allocator>
std::size_t read_at(SyncRandomAccessReadDevice& d,
    uint64_t offset, basic_streambuf<Allocator>& b,
    asio::error_code& ec);


template <typename SyncRandomAccessReadDevice, typename Allocator,
    typename CompletionCondition>
std::size_t read_at(SyncRandomAccessReadDevice& d,
    uint64_t offset, basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition);


template <typename SyncRandomAccessReadDevice, typename Allocator,
    typename CompletionCondition>
std::size_t read_at(SyncRandomAccessReadDevice& d,
    uint64_t offset, basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition, asio::error_code& ec);

#endif // !defined(ASIO_NO_IOSTREAM)


template <typename AsyncRandomAccessReadDevice, typename MutableBufferSequence,
    typename ReadHandler>
ASIO_INITFN_RESULT_TYPE(ReadHandler,
    void (asio::error_code, std::size_t))
async_read_at(AsyncRandomAccessReadDevice& d, uint64_t offset,
    const MutableBufferSequence& buffers,
    ASIO_MOVE_ARG(ReadHandler) handler);


template <typename AsyncRandomAccessReadDevice, typename MutableBufferSequence,
    typename CompletionCondition, typename ReadHandler>
ASIO_INITFN_RESULT_TYPE(ReadHandler,
    void (asio::error_code, std::size_t))
async_read_at(AsyncRandomAccessReadDevice& d,
    uint64_t offset, const MutableBufferSequence& buffers,
    CompletionCondition completion_condition,
    ASIO_MOVE_ARG(ReadHandler) handler);

#if !defined(ASIO_NO_IOSTREAM)


template <typename AsyncRandomAccessReadDevice, typename Allocator,
    typename ReadHandler>
ASIO_INITFN_RESULT_TYPE(ReadHandler,
    void (asio::error_code, std::size_t))
async_read_at(AsyncRandomAccessReadDevice& d, uint64_t offset,
    basic_streambuf<Allocator>& b, ASIO_MOVE_ARG(ReadHandler) handler);


template <typename AsyncRandomAccessReadDevice, typename Allocator,
    typename CompletionCondition, typename ReadHandler>
ASIO_INITFN_RESULT_TYPE(ReadHandler,
    void (asio::error_code, std::size_t))
async_read_at(AsyncRandomAccessReadDevice& d,
    uint64_t offset, basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition,
    ASIO_MOVE_ARG(ReadHandler) handler);

#endif // !defined(ASIO_NO_IOSTREAM)

/*@}*/

} // namespace asio

#include "asio/detail/pop_options.hpp"

#include "asio/impl/read_at.hpp"

#endif // ASIO_READ_AT_HPP
