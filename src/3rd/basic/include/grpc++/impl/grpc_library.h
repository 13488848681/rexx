
#ifndef GRPCXX_IMPL_GRPC_LIBRARY_H
#define GRPCXX_IMPL_GRPC_LIBRARY_H

#include <iostream>

#include <grpc++/impl/codegen/config.h>
#include <grpc++/impl/codegen/core_codegen.h>
#include <grpc++/impl/codegen/grpc_library.h>
#include <grpc/grpc.h>

namespace grpc {

namespace internal {
class GrpcLibrary final : public GrpcLibraryInterface {
 public:
  void init() override { grpc_init(); }
  void shutdown() override { grpc_shutdown(); }
};

static GrpcLibrary g_gli;
static CoreCodegen g_core_codegen;

/// Instantiating this class ensures the proper initialization of gRPC.
class GrpcLibraryInitializer final {
 public:
  GrpcLibraryInitializer() {
    if (grpc::g_glip == nullptr) {
      grpc::g_glip = &g_gli;
    }
    if (grpc::g_core_codegen_interface == nullptr) {
      grpc::g_core_codegen_interface = &g_core_codegen;
    }
  }

  /// A no-op method to force the linker to reference this class, which will
  /// take care of initializing and shutting down the gRPC runtime.
  int summon() { return 0; }
};

}  // namespace internal
}  // namespace grpc

#endif  // GRPCXX_IMPL_GRPC_LIBRARY_H
