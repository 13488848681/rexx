
#ifndef GRPCXX_IMPL_CHANNEL_ARGUMENT_OPTION_H
#define GRPCXX_IMPL_CHANNEL_ARGUMENT_OPTION_H

#include <map>
#include <memory>

#include <grpc++/impl/server_builder_option.h>
#include <grpc++/support/channel_arguments.h>

namespace grpc {

std::unique_ptr<ServerBuilderOption> MakeChannelArgumentOption(
    const grpc::string &name, const grpc::string &value);
std::unique_ptr<ServerBuilderOption> MakeChannelArgumentOption(
    const grpc::string &name, int value);

}  // namespace grpc

#endif  // GRPCXX_IMPL_CHANNEL_ARGUMENT_OPTION_H
