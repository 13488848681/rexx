
#ifndef GRPC_SUPPORT_TLS_PTHREAD_H
#define GRPC_SUPPORT_TLS_PTHREAD_H

#include <grpc/support/log.h> /* for GPR_ASSERT */
#include <pthread.h>

/* Thread local storage based on pthread library calls.
   #include tls.h to use this - and see that file for documentation */

struct gpr_pthread_thread_local {
  pthread_key_t key;
};

#define GPR_TLS_DECL(name) static struct gpr_pthread_thread_local name = {0}

#define gpr_tls_init(tls) GPR_ASSERT(0 == pthread_key_create(&(tls)->key, NULL))
#define gpr_tls_destroy(tls) pthread_key_delete((tls)->key)
#define gpr_tls_get(tls) ((intptr_t)pthread_getspecific((tls)->key))
#ifdef __cplusplus
extern "C" {
#endif
intptr_t gpr_tls_set(struct gpr_pthread_thread_local *tls, intptr_t value);
#ifdef __cplusplus
}
#endif

#endif /* GRPC_SUPPORT_TLS_PTHREAD_H */
