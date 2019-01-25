
#ifndef ASIO_VERSION_HPP
#define ASIO_VERSION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

// ASIO_VERSION % 100 is the sub-minor version
// ASIO_VERSION / 100 % 1000 is the minor version
// ASIO_VERSION / 100000 is the major version
#define ASIO_VERSION 101006 // 1.10.6

#endif // ASIO_VERSION_HPP
