
#ifndef GRPC_IMPL_CODEGEN_SYNC_H
#define GRPC_IMPL_CODEGEN_SYNC_H
/* Synchronization primitives for GPR.

   The type  gpr_mu              provides a non-reentrant mutex (lock).

   The type  gpr_cv              provides a condition variable.

   The type  gpr_once            provides for one-time initialization.

   The type gpr_event            provides one-time-setting, reading, and
                                 waiting of a void*, with memory barriers.

   The type gpr_refcount         provides an object reference counter,
                                 with memory barriers suitable to control
                                 object lifetimes.

   The type gpr_stats_counter    provides an atomic statistics counter. It
                                 provides no memory barriers.
 */

#ifdef __cplusplus
extern "C" {
#endif

/* Platform-specific type declarations of gpr_mu and gpr_cv.   */
#include <grpc/impl/codegen/port_platform.h>
#include <grpc/impl/codegen/sync_generic.h>

#if defined(GPR_POSIX_SYNC)
#include <grpc/impl/codegen/sync_posix.h>
#elif defined(GPR_WINDOWS)
#include <grpc/impl/codegen/sync_windows.h>
#elif !defined(GPR_CUSTOM_SYNC)
#error Unable to determine platform for sync
#endif

#ifdef __cplusplus
}
#endif

#endif /* GRPC_IMPL_CODEGEN_SYNC_H */
