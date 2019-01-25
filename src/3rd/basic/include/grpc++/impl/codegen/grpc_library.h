
#ifndef GRPCXX_IMPL_CODEGEN_GRPC_LIBRARY_H
#define GRPCXX_IMPL_CODEGEN_GRPC_LIBRARY_H

#include <grpc++/impl/codegen/core_codegen_interface.h>

namespace grpc {

class GrpcLibraryInterface {
 public:
  virtual void init() = 0;
  virtual void shutdown() = 0;
};

/// Initialized by \a grpc::GrpcLibraryInitializer from
/// <grpc++/impl/grpc_library.h>
extern GrpcLibraryInterface* g_glip;

/// Classes that require gRPC to be initialized should inherit from this class.
class GrpcLibraryCodegen {
 public:
  GrpcLibraryCodegen(bool call_grpc_init = true) : grpc_init_called_(false) {
    if (call_grpc_init) {
      GPR_CODEGEN_ASSERT(g_glip &&
                         "gRPC library not initialized. See "
                         "grpc::internal::GrpcLibraryInitializer.");
      g_glip->init();
      grpc_init_called_ = true;
    }
  }
  virtual ~GrpcLibraryCodegen() {
    if (grpc_init_called_) {
      GPR_CODEGEN_ASSERT(g_glip &&
                         "gRPC library not initialized. See "
                         "grpc::internal::GrpcLibraryInitializer.");
      g_glip->shutdown();
    }
  }

 private:
  bool grpc_init_called_;
};

}  // namespace grpc

#endif  // GRPCXX_IMPL_CODEGEN_GRPC_LIBRARY_H
