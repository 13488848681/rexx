
#ifndef GRPC_SUPPORT_TLS_MSVC_H
#define GRPC_SUPPORT_TLS_MSVC_H

/* Thread local storage based on ms visual c compiler primitives.
   #include tls.h to use this - and see that file for documentation */

struct gpr_msvc_thread_local {
  intptr_t value;
};

#define GPR_TLS_DECL(name) \
  static __declspec(thread) struct gpr_msvc_thread_local name = {0}

#define gpr_tls_init(tls) \
  do {                    \
  } while (0)
#define gpr_tls_destroy(tls) \
  do {                       \
  } while (0)
#define gpr_tls_set(tls, new_value) (((tls)->value) = (new_value))
#define gpr_tls_get(tls) ((tls)->value)

#endif /* GRPC_SUPPORT_TLS_MSVC_H */
