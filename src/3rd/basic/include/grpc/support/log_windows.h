
#ifndef GRPC_SUPPORT_LOG_WINDOWS_H
#define GRPC_SUPPORT_LOG_WINDOWS_H

#include <grpc/impl/codegen/port_platform.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Returns a string allocated with gpr_malloc that contains a UTF-8
 * formatted error message, corresponding to the error messageid.
 * Use in conjunction with GetLastError() et al.
 */
GPRAPI char *gpr_format_message(int messageid);

#ifdef __cplusplus
}
#endif

#endif /* GRPC_SUPPORT_LOG_WINDOWS_H */
