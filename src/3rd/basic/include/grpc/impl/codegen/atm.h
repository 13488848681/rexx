
#ifndef GRPC_IMPL_CODEGEN_ATM_H
#define GRPC_IMPL_CODEGEN_ATM_H


#include <grpc/impl/codegen/port_platform.h>

#if defined(GPR_GCC_ATOMIC)
#include <grpc/impl/codegen/atm_gcc_atomic.h>
#elif defined(GPR_GCC_SYNC)
#include <grpc/impl/codegen/atm_gcc_sync.h>
#elif defined(GPR_WINDOWS_ATOMIC)
#include <grpc/impl/codegen/atm_windows.h>
#else
#error could not determine platform for atm
#endif

/** Adds \a delta to \a *value, clamping the result to the range specified
    by \a min and \a max.  Returns the new value. */
gpr_atm gpr_atm_no_barrier_clamped_add(gpr_atm *value, gpr_atm delta,
                                       gpr_atm min, gpr_atm max);

#endif /* GRPC_IMPL_CODEGEN_ATM_H */
