
#ifndef GRPC_IMPL_CODEGEN_SYNC_WINDOWS_H
#define GRPC_IMPL_CODEGEN_SYNC_WINDOWS_H

#include <grpc/impl/codegen/sync_generic.h>

typedef struct {
  CRITICAL_SECTION cs; /* Not an SRWLock until Vista is unsupported */
  int locked;
} gpr_mu;

typedef CONDITION_VARIABLE gpr_cv;

typedef INIT_ONCE gpr_once;
#define GPR_ONCE_INIT INIT_ONCE_STATIC_INIT

#endif /* GRPC_IMPL_CODEGEN_SYNC_WINDOWS_H */
