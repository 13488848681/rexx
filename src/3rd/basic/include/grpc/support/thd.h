
#ifndef GRPC_SUPPORT_THD_H
#define GRPC_SUPPORT_THD_H

#include <grpc/support/port_platform.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uintptr_t gpr_thd_id;

/* Thread creation options. */
typedef struct {
  int flags; /* Opaque field. Get and set with accessors below. */
} gpr_thd_options;

/* Create a new thread running (*thd_body)(arg) and place its thread identifier
   in *t, and return true.  If there are insufficient resources, return false.
   If options==NULL, default options are used.
   The thread is immediately runnable, and exits when (*thd_body)() returns.  */
GPRAPI int gpr_thd_new(gpr_thd_id *t, void (*thd_body)(void *arg), void *arg,
                       const gpr_thd_options *options);

/* Return a gpr_thd_options struct with all fields set to defaults. */
GPRAPI gpr_thd_options gpr_thd_options_default(void);

/* Set the thread to become detached on startup - this is the default. */
GPRAPI void gpr_thd_options_set_detached(gpr_thd_options *options);

/* Set the thread to become joinable - mutually exclusive with detached. */
GPRAPI void gpr_thd_options_set_joinable(gpr_thd_options *options);

/* Returns non-zero if the option detached is set. */
GPRAPI int gpr_thd_options_is_detached(const gpr_thd_options *options);

/* Returns non-zero if the option joinable is set. */
GPRAPI int gpr_thd_options_is_joinable(const gpr_thd_options *options);

/* Returns the identifier of the current thread. */
GPRAPI gpr_thd_id gpr_thd_currentid(void);

/* Blocks until the specified thread properly terminates.
   Calling this on a detached thread has unpredictable results. */
GPRAPI void gpr_thd_join(gpr_thd_id t);

#ifdef __cplusplus
}
#endif

#endif /* GRPC_SUPPORT_THD_H */
