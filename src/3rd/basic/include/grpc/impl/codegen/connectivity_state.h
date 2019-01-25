
#ifndef GRPC_IMPL_CODEGEN_CONNECTIVITY_STATE_H
#define GRPC_IMPL_CODEGEN_CONNECTIVITY_STATE_H

#ifdef __cplusplus
extern "C" {
#endif

/** Connectivity state of a channel. */
typedef enum {
  /** channel has just been initialized */
  GRPC_CHANNEL_INIT = -1,
  /** channel is idle */
  GRPC_CHANNEL_IDLE,
  /** channel is connecting */
  GRPC_CHANNEL_CONNECTING,
  /** channel is ready for work */
  GRPC_CHANNEL_READY,
  /** channel has seen a failure but expects to recover */
  GRPC_CHANNEL_TRANSIENT_FAILURE,
  /** channel has seen a failure that it cannot recover from */
  GRPC_CHANNEL_SHUTDOWN
} grpc_connectivity_state;

#ifdef __cplusplus
}
#endif

#endif /* GRPC_IMPL_CODEGEN_CONNECTIVITY_STATE_H */
