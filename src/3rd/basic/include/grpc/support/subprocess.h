
#ifndef GRPC_SUPPORT_SUBPROCESS_H
#define GRPC_SUPPORT_SUBPROCESS_H

#include <grpc/support/port_platform.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct gpr_subprocess gpr_subprocess;

/* .exe on windows, empty on unices */
GPRAPI const char *gpr_subprocess_binary_extension();

GPRAPI gpr_subprocess *gpr_subprocess_create(int argc, const char **argv);
/* if subprocess has not been joined, kill it */
GPRAPI void gpr_subprocess_destroy(gpr_subprocess *p);
/* returns exit status; can be called at most once */
GPRAPI int gpr_subprocess_join(gpr_subprocess *p);
GPRAPI void gpr_subprocess_interrupt(gpr_subprocess *p);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif /* GRPC_SUPPORT_SUBPROCESS_H */
