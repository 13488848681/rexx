
#ifndef GRPC_IMPL_CODEGEN_PROPAGATION_BITS_H
#define GRPC_IMPL_CODEGEN_PROPAGATION_BITS_H

#include <grpc/impl/codegen/port_platform.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Propagation bits: this can be bitwise or-ed to form propagation_mask for
 * grpc_call */
/** Propagate deadline */
#define GRPC_PROPAGATE_DEADLINE ((uint32_t)1)
/** Propagate census context */
#define GRPC_PROPAGATE_CENSUS_STATS_CONTEXT ((uint32_t)2)
#define GRPC_PROPAGATE_CENSUS_TRACING_CONTEXT ((uint32_t)4)
/** Propagate cancellation */
#define GRPC_PROPAGATE_CANCELLATION ((uint32_t)8)

#define GRPC_PROPAGATE_DEFAULTS                                                \
  ((uint32_t)((                                                                \
      0xffff | GRPC_PROPAGATE_DEADLINE | GRPC_PROPAGATE_CENSUS_STATS_CONTEXT | \
      GRPC_PROPAGATE_CENSUS_TRACING_CONTEXT | GRPC_PROPAGATE_CANCELLATION)))

#ifdef __cplusplus
}
#endif

#endif /* GRPC_IMPL_CODEGEN_PROPAGATION_BITS_H */
