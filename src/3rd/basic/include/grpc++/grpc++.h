


#ifndef GRPCXX_GRPCXX_H
#define GRPCXX_GRPCXX_H

// Pragma for http://include-what-you-use.org/ tool, tells that following
// headers are not private for grpc++.h and are part of its interface.
// IWYU pragma: begin_exports
#include <grpc/grpc.h>

#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/completion_queue.h>
#include <grpc++/create_channel.h>
#include <grpc++/create_channel_posix.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <grpc++/server_posix.h>
// IWYU pragma: end_exports

namespace grpc {
grpc::string Version();
}  // namespace grpc

#endif  // GRPCXX_GRPCXX_H
