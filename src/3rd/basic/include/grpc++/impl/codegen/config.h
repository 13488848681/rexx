
#ifndef GRPCXX_IMPL_CODEGEN_CONFIG_H
#define GRPCXX_IMPL_CODEGEN_CONFIG_H

#ifndef GRPC_CUSTOM_STRING
#include <string>
#define GRPC_CUSTOM_STRING std::string
#endif

#define GRPC_OVERRIDE override  // deprecated
#define GRPC_FINAL final        // deprecated

namespace grpc {

typedef GRPC_CUSTOM_STRING string;

using std::to_string;

}  // namespace grpc

#endif  // GRPCXX_IMPL_CODEGEN_CONFIG_H
