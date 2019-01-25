
#ifndef GRPC_SUPPORT_TLS_H
#define GRPC_SUPPORT_TLS_H

#include <grpc/support/port_platform.h>

/* Thread local storage.

   A minimal wrapper that should be implementable across many compilers,
   and implementable efficiently across most modern compilers.

   Thread locals have type intptr_t.

   Declaring a thread local variable 'foo':
     GPR_TLS_DECL(foo);
   Thread locals always have static scope.

   Initializing a thread local (must be done at library initialization
   time):
     gpr_tls_init(&foo);

   Destroying a thread local:
     gpr_tls_destroy(&foo);

   Setting a thread local (returns new_value):
     gpr_tls_set(&foo, new_value);

   Accessing a thread local:
     current_value = gpr_tls_get(&foo);

   ALL functions here may be implemented as macros. */

#ifdef GPR_GCC_TLS
#include <grpc/support/tls_gcc.h>
#endif

#ifdef GPR_MSVC_TLS
#include <grpc/support/tls_msvc.h>
#endif

#ifdef GPR_PTHREAD_TLS
#include <grpc/support/tls_pthread.h>
#endif

#endif /* GRPC_SUPPORT_TLS_H */
