
#ifndef GRPCXX_IMPL_CODEGEN_CALL_HOOK_H
#define GRPCXX_IMPL_CODEGEN_CALL_HOOK_H

namespace grpc {

class CallOpSetInterface;
class Call;

/// Channel and Server implement this to allow them to hook performing ops
class CallHook {
 public:
  virtual ~CallHook() {}
  virtual void PerformOpsOnCall(CallOpSetInterface* ops, Call* call) = 0;
};

}  // namespace grpc

#endif  // GRPCXX_IMPL_CODEGEN_CALL_HOOK_H
