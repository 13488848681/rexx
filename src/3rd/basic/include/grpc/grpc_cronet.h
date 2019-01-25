
#ifndef GRPC_GRPC_CRONET_H
#define GRPC_GRPC_CRONET_H

#include <grpc/grpc.h>

#ifdef __cplusplus
extern "C" {
#endif

GRPCAPI grpc_channel *grpc_cronet_secure_channel_create(
    void *engine, const char *target, const grpc_channel_args *args,
    void *reserved);

#ifdef __cplusplus
}
#endif

#endif /* GRPC_GRPC_CRONET_H */
