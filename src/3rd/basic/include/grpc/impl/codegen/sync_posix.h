
#ifndef GRPC_IMPL_CODEGEN_SYNC_POSIX_H
#define GRPC_IMPL_CODEGEN_SYNC_POSIX_H

#include <grpc/impl/codegen/sync_generic.h>

#include <pthread.h>

typedef pthread_mutex_t gpr_mu;
typedef pthread_cond_t gpr_cv;
typedef pthread_once_t gpr_once;

#define GPR_ONCE_INIT PTHREAD_ONCE_INIT

#endif /* GRPC_IMPL_CODEGEN_SYNC_POSIX_H */
