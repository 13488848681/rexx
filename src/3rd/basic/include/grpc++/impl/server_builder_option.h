
#ifndef GRPCXX_IMPL_SERVER_BUILDER_OPTION_H
#define GRPCXX_IMPL_SERVER_BUILDER_OPTION_H

#include <map>
#include <memory>

#include <grpc++/impl/server_builder_plugin.h>
#include <grpc++/support/channel_arguments.h>

namespace grpc {

/// Interface to pass an option to a \a ServerBuilder.
class ServerBuilderOption {
 public:
  virtual ~ServerBuilderOption() {}
  /// Alter the \a ChannelArguments used to create the gRPC server.
  virtual void UpdateArguments(ChannelArguments* args) = 0;
  /// Alter the ServerBuilderPlugin map that will be added into ServerBuilder.
  virtual void UpdatePlugins(
      std::vector<std::unique_ptr<ServerBuilderPlugin>>* plugins) = 0;
};

}  // namespace grpc

#endif  // GRPCXX_IMPL_SERVER_BUILDER_OPTION_H
