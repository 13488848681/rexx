
#ifndef GRPCXX_SERVER_POSIX_H
#define GRPCXX_SERVER_POSIX_H

#include <memory>

#include <grpc++/server.h>
#include <grpc/support/port_platform.h>

namespace grpc {

#ifdef GPR_SUPPORT_CHANNELS_FROM_FD

/// Adds new client to a \a Server communicating over given file descriptor
///
/// \param server The server to add a client to.
/// \param fd The file descriptor representing a socket.
void AddInsecureChannelFromFd(Server* server, int fd);

#endif  // GPR_SUPPORT_CHANNELS_FROM_FD

}  // namespace grpc

#endif  // GRPCXX_SERVER_POSIX_H
