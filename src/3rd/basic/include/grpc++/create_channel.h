
#ifndef GRPCXX_CREATE_CHANNEL_H
#define GRPCXX_CREATE_CHANNEL_H

#include <memory>

#include <grpc++/channel.h>
#include <grpc++/security/credentials.h>
#include <grpc++/support/channel_arguments.h>
#include <grpc++/support/config.h>

namespace grpc {


std::shared_ptr<Channel> CreateChannel(
    const grpc::string& target,
    const std::shared_ptr<ChannelCredentials>& creds);


std::shared_ptr<Channel> CreateCustomChannel(
    const grpc::string& target,
    const std::shared_ptr<ChannelCredentials>& creds,
    const ChannelArguments& args);

}  // namespace grpc

#endif  // GRPCXX_CREATE_CHANNEL_H
