

#ifndef _SLJIT_CONFIG_H_
#define _SLJIT_CONFIG_H_

#ifndef SLJIT_UTIL_GLOBAL_LOCK
/* Enabled by default */
#define SLJIT_UTIL_GLOBAL_LOCK 1
#endif

/* Implements a stack like data structure (by using mmap / VirtualAlloc). */
#ifndef SLJIT_UTIL_STACK
/* Enabled by default */
#define SLJIT_UTIL_STACK 1
#endif

/* Single threaded application. Does not require any locks. */
#ifndef SLJIT_SINGLE_THREADED
/* Disabled by default. */
#define SLJIT_SINGLE_THREADED 0
#endif

/* --------------------------------------------------------------------- */
/*  Configuration                                                        */
/* --------------------------------------------------------------------- */

/* If SLJIT_STD_MACROS_DEFINED is not defined, the application should
   define SLJIT_MALLOC, SLJIT_FREE, SLJIT_MEMMOVE, and NULL. */
#ifndef SLJIT_STD_MACROS_DEFINED
/* Disabled by default. */
#define SLJIT_STD_MACROS_DEFINED 0
#endif

/* Executable code allocation:
   If SLJIT_EXECUTABLE_ALLOCATOR is not defined, the application should
   define both SLJIT_MALLOC_EXEC and SLJIT_FREE_EXEC. */
#ifndef SLJIT_EXECUTABLE_ALLOCATOR
/* Enabled by default. */
#define SLJIT_EXECUTABLE_ALLOCATOR 1
#endif

/* Force cdecl calling convention even if a better calling
   convention (e.g. fastcall) is supported by the C compiler.
   If this option is enabled, C functions without
   SLJIT_CALL can also be called from JIT code. */
#ifndef SLJIT_USE_CDECL_CALLING_CONVENTION
/* Disabled by default */
#define SLJIT_USE_CDECL_CALLING_CONVENTION 0
#endif

/* Return with error when an invalid argument is passed. */
#ifndef SLJIT_ARGUMENT_CHECKS
/* Disabled by default */
#define SLJIT_ARGUMENT_CHECKS 0
#endif

/* Debug checks (assertions, etc.). */
#ifndef SLJIT_DEBUG
/* Enabled by default */
#define SLJIT_DEBUG 1
#endif

/* Verbose operations. */
#ifndef SLJIT_VERBOSE
/* Enabled by default */
#define SLJIT_VERBOSE 1
#endif

/*
  SLJIT_IS_FPU_AVAILABLE
    The availability of the FPU can be controlled by SLJIT_IS_FPU_AVAILABLE.
      zero value - FPU is NOT present.
      nonzero value - FPU is present.
*/

/* For further configurations, see the beginning of sljitConfigInternal.h */

#endif
