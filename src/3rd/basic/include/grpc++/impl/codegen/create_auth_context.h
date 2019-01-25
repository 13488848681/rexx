
#ifndef GRPCXX_IMPL_CODEGEN_CREATE_AUTH_CONTEXT_H
#define GRPCXX_IMPL_CODEGEN_CREATE_AUTH_CONTEXT_H

#include <memory>

#include <grpc++/impl/codegen/security/auth_context.h>
#include <grpc/impl/codegen/grpc_types.h>

namespace grpc {

std::shared_ptr<const AuthContext> CreateAuthContext(grpc_call* call);

}  // namespace grpc

#endif  // GRPCXX_IMPL_CODEGEN_CREATE_AUTH_CONTEXT_H
