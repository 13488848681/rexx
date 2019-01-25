
#ifndef GRPCXX_CREATE_CHANNEL_POSIX_H
#define GRPCXX_CREATE_CHANNEL_POSIX_H

#include <memory>

#include <grpc++/channel.h>
#include <grpc++/support/channel_arguments.h>
#include <grpc/support/port_platform.h>

namespace grpc {

#ifdef GPR_SUPPORT_CHANNELS_FROM_FD

/// Create a new \a Channel communicating over given file descriptor
///
/// \param target The name of the target.
/// \param fd The file descriptor representing a socket.
std::shared_ptr<Channel> CreateInsecureChannelFromFd(const grpc::string& target,
                                                     int fd);

/// Create a new \a Channel communicating over given file descriptor with custom
/// channel arguments
///
/// \param target The name of the target.
/// \param fd The file descriptor representing a socket.
/// \param args Options for channel creation.
std::shared_ptr<Channel> CreateCustomInsecureChannelFromFd(
    const grpc::string& target, int fd, const ChannelArguments& args);

#endif  // GPR_SUPPORT_CHANNELS_FROM_FD

}  // namespace grpc

#endif  // GRPCXX_CREATE_CHANNEL_POSIX_H
