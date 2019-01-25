
#ifndef GRPCXX_CHANNEL_H
#define GRPCXX_CHANNEL_H

#include <memory>

#include <grpc++/impl/call.h>
#include <grpc++/impl/codegen/channel_interface.h>
#include <grpc++/impl/codegen/config.h>
#include <grpc++/impl/codegen/grpc_library.h>
#include <grpc/grpc.h>

struct grpc_channel;

namespace grpc {
/// Channels represent a connection to an endpoint. Created by \a CreateChannel.
class Channel final : public ChannelInterface,
                      public CallHook,
                      public std::enable_shared_from_this<Channel>,
                      private GrpcLibraryCodegen {
 public:
  ~Channel();

  /// Get the current channel state. If the channel is in IDLE and
  /// \a try_to_connect is set to true, try to connect.
  grpc_connectivity_state GetState(bool try_to_connect) override;

  /// Returns the LB policy name, or the empty string if not yet available.
  grpc::string GetLoadBalancingPolicyName() const;

  /// Returns the service config in JSON form, or the empty string if
  /// not available.
  grpc::string GetServiceConfigJSON() const;

 private:
  template <class InputMessage, class OutputMessage>
  friend Status BlockingUnaryCall(ChannelInterface* channel,
                                  const RpcMethod& method,
                                  ClientContext* context,
                                  const InputMessage& request,
                                  OutputMessage* result);
  friend std::shared_ptr<Channel> CreateChannelInternal(
      const grpc::string& host, grpc_channel* c_channel);
  Channel(const grpc::string& host, grpc_channel* c_channel);

  Call CreateCall(const RpcMethod& method, ClientContext* context,
                  CompletionQueue* cq) override;
  void PerformOpsOnCall(CallOpSetInterface* ops, Call* call) override;
  void* RegisterMethod(const char* method) override;

  void NotifyOnStateChangeImpl(grpc_connectivity_state last_observed,
                               gpr_timespec deadline, CompletionQueue* cq,
                               void* tag) override;
  bool WaitForStateChangeImpl(grpc_connectivity_state last_observed,
                              gpr_timespec deadline) override;

  const grpc::string host_;
  grpc_channel* const c_channel_;  // owned
};

}  // namespace grpc

#endif  // GRPCXX_CHANNEL_H
