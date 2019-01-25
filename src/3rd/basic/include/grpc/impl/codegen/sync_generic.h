
#ifndef GRPC_IMPL_CODEGEN_SYNC_GENERIC_H
#define GRPC_IMPL_CODEGEN_SYNC_GENERIC_H
/* Generic type defintions for gpr_sync. */

#include <grpc/impl/codegen/atm.h>

/* gpr_event */
typedef struct { gpr_atm state; } gpr_event;

#define GPR_EVENT_INIT \
  { 0 }

/* gpr_refcount */
typedef struct { gpr_atm count; } gpr_refcount;

/* gpr_stats_counter */
typedef struct { gpr_atm value; } gpr_stats_counter;

#define GPR_STATS_INIT \
  { 0 }

#endif /* GRPC_IMPL_CODEGEN_SYNC_GENERIC_H */
