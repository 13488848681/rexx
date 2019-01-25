
#ifndef GRPCXX_IMPL_CODEGEN_RPC_METHOD_H
#define GRPCXX_IMPL_CODEGEN_RPC_METHOD_H

#include <memory>

#include <grpc++/impl/codegen/channel_interface.h>

namespace grpc {

class RpcMethod {
 public:
  enum RpcType {
    NORMAL_RPC = 0,
    CLIENT_STREAMING,  // request streaming
    SERVER_STREAMING,  // response streaming
    BIDI_STREAMING
  };

  RpcMethod(const char* name, RpcType type)
      : name_(name), method_type_(type), channel_tag_(NULL) {}

  RpcMethod(const char* name, RpcType type,
            const std::shared_ptr<ChannelInterface>& channel)
      : name_(name),
        method_type_(type),
        channel_tag_(channel->RegisterMethod(name)) {}

  const char* name() const { return name_; }
  RpcType method_type() const { return method_type_; }
  void SetMethodType(RpcType type) { method_type_ = type; }
  void* channel_tag() const { return channel_tag_; }

 private:
  const char* const name_;
  RpcType method_type_;
  void* const channel_tag_;
};

}  // namespace grpc

#endif  // GRPCXX_IMPL_CODEGEN_RPC_METHOD_H
