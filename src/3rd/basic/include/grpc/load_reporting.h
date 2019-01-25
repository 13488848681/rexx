
#ifndef GRPC_LOAD_REPORTING_H
#define GRPC_LOAD_REPORTING_H

#include <grpc/impl/codegen/port_platform.h>
#include <grpc/slice.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Metadata key for the gRPC LB load balancer token.
 *
 * The value corresponding to this key is an opaque token that is given to the
 * frontend as part of each pick; the frontend sends this token to the backend
 * in each request it sends when using that pick. The token is used by the
 * backend to verify the request and to allow the backend to report load to the
 * gRPC LB system. */
#define GRPC_LB_TOKEN_MD_KEY "lb-token"

/** A sequence of values for load reporting purposes */
typedef struct grpc_load_reporting_cost_context {
  grpc_slice *values;
  size_t values_count;
} grpc_load_reporting_cost_context;

#ifdef __cplusplus
}
#endif

#endif /* GRPC_LOAD_REPORTING_H */
