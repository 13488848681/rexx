
#ifndef GRPCXX_IMPL_CODEGEN_STATUS_HELPER_H
#define GRPCXX_IMPL_CODEGEN_STATUS_HELPER_H

#include <grpc++/impl/codegen/status.h>

namespace grpc {

inline StatusCode GetCanonicalCode(const Status& status) {
  return status.error_code();
}

}  // namespace grpc

#endif  // GRPCXX_IMPL_CODEGEN_STATUS_HELPER_H
