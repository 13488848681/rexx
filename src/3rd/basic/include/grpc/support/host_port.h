
#ifndef GRPC_SUPPORT_HOST_PORT_H
#define GRPC_SUPPORT_HOST_PORT_H

#include <grpc/support/port_platform.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Given a host and port, creates a newly-allocated string of the form
   "host:port" or "[ho:st]:port", depending on whether the host contains colons
   like an IPv6 literal.  If the host is already bracketed, then additional
   brackets will not be added.

   Usage is similar to gpr_asprintf: returns the number of bytes written
   (excluding the final '\0'), and *out points to a string which must later be
   destroyed using gpr_free().

   In the unlikely event of an error, returns -1 and sets *out to NULL. */
GPRAPI int gpr_join_host_port(char **out, const char *host, int port);

/* Given a name in the form "host:port" or "[ho:st]:port", split into hostname
   and port number, into newly allocated strings, which must later be
   destroyed using gpr_free().
   Return 1 on success, 0 on failure. Guarantees *host and *port == NULL on
   failure. */
GPRAPI int gpr_split_host_port(const char *name, char **host, char **port);

#ifdef __cplusplus
}
#endif

#endif /* GRPC_SUPPORT_HOST_PORT_H */
