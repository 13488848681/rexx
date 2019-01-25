
#ifndef GRPCXX_IMPL_SERVER_BUILDER_PLUGIN_H
#define GRPCXX_IMPL_SERVER_BUILDER_PLUGIN_H

#include <memory>

#include <grpc++/support/config.h>

namespace grpc {

class ServerInitializer;
class ChannelArguments;

class ServerBuilderPlugin {
 public:
  virtual ~ServerBuilderPlugin() {}
  virtual grpc::string name() = 0;

  // InitServer will be called in ServerBuilder::BuildAndStart(), after the
  // Server instance is created.
  virtual void InitServer(ServerInitializer* si) = 0;

  // Finish will be called at the end of ServerBuilder::BuildAndStart().
  virtual void Finish(ServerInitializer* si) = 0;

  // ChangeArguments is an interface that can be used in
  // ServerBuilderOption::UpdatePlugins
  virtual void ChangeArguments(const grpc::string& name, void* value) = 0;

  // UpdateChannelArguments will be called in ServerBuilder::BuildAndStart(),
  // before the Server instance is created.
  virtual void UpdateChannelArguments(ChannelArguments* args) {}

  virtual bool has_sync_methods() const { return false; }
  virtual bool has_async_methods() const { return false; }
};

}  // namespace grpc

#endif  // GRPCXX_IMPL_SERVER_BUILDER_PLUGIN_H
