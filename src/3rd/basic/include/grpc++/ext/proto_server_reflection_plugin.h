
#ifndef GRPCXX_EXT_PROTO_SERVER_REFLECTION_PLUGIN_H
#define GRPCXX_EXT_PROTO_SERVER_REFLECTION_PLUGIN_H

#include <grpc++/impl/server_builder_plugin.h>
#include <grpc++/support/config.h>

namespace grpc {
class ServerInitializer;
class ProtoServerReflection;
}  // namespace grpc

namespace grpc {
namespace reflection {

class ProtoServerReflectionPlugin : public ::grpc::ServerBuilderPlugin {
 public:
  ProtoServerReflectionPlugin();
  ::grpc::string name() override;
  void InitServer(::grpc::ServerInitializer* si) override;
  void Finish(::grpc::ServerInitializer* si) override;
  void ChangeArguments(const ::grpc::string& name, void* value) override;
  bool has_async_methods() const override;
  bool has_sync_methods() const override;

 private:
  std::shared_ptr<grpc::ProtoServerReflection> reflection_service_;
};

// Add proto reflection plugin to ServerBuilder. This function should be called
// at the static initialization time.
void InitProtoReflectionServerBuilderPlugin();

}  // namespace reflection
}  // namespace grpc

#endif  // GRPCXX_EXT_PROTO_SERVER_REFLECTION_PLUGIN_H
