
#ifndef GRPC_GRPC_POSIX_H
#define GRPC_GRPC_POSIX_H

#include <grpc/impl/codegen/grpc_types.h>
#include <grpc/support/port_platform.h>

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/*! \mainpage GRPC Core POSIX
 *
 * The GRPC Core POSIX library provides some POSIX-specific low-level
 * functionality on top of GRPC Core.
 */

/** Create a client channel to 'target' using file descriptor 'fd'. The 'target'
    argument will be used to indicate the name for this channel. See the comment
    for grpc_insecure_channel_create for description of 'args' argument. */
GRPCAPI grpc_channel *grpc_insecure_channel_create_from_fd(
    const char *target, int fd, const grpc_channel_args *args);

/** Add the connected communication channel based on file descriptor 'fd' to the
    'server'. The 'fd' must be an open file descriptor corresponding to a
    connected socket. Events from the file descriptor may come on any of the
    server completion queues (i.e completion queues registered via the
    grpc_server_register_completion_queue API).

    The 'reserved' pointer MUST be NULL.
    */
GRPCAPI void grpc_server_add_insecure_channel_from_fd(grpc_server *server,
                                                      void *reserved, int fd);

/** GRPC Core POSIX library may internally use signals to optimize some work.
   The library uses (SIGRTMIN + 6) signal by default. Use this API to instruct
   the library to use a different signal i.e 'signum' instead.
   Note:
   - To prevent GRPC library from using any signals, pass a 'signum' of -1
   - This API is optional but if called, it MUST be called before grpc_init() */
GRPCAPI void grpc_use_signal(int signum);

#ifdef __cplusplus
}
#endif

#endif /* GRPC_GRPC_POSIX_H */
