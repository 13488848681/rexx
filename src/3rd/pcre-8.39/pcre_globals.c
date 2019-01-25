

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "pcre_internal.h"

#if defined _MSC_VER || defined  __SYMBIAN32__
static void* LocalPcreMalloc(size_t aSize)
  {
  return malloc(aSize);
  }
static void LocalPcreFree(void* aPtr)
  {
  free(aPtr);
  }
PCRE_EXP_DATA_DEFN void *(*PUBL(malloc))(size_t) = LocalPcreMalloc;
PCRE_EXP_DATA_DEFN void  (*PUBL(free))(void *) = LocalPcreFree;
PCRE_EXP_DATA_DEFN void *(*PUBL(stack_malloc))(size_t) = LocalPcreMalloc;
PCRE_EXP_DATA_DEFN void  (*PUBL(stack_free))(void *) = LocalPcreFree;
PCRE_EXP_DATA_DEFN int   (*PUBL(callout))(PUBL(callout_block) *) = NULL;
PCRE_EXP_DATA_DEFN int   (*PUBL(stack_guard))(void) = NULL;

#elif !defined VPCOMPAT
PCRE_EXP_DATA_DEFN void *(*PUBL(malloc))(size_t) = malloc;
PCRE_EXP_DATA_DEFN void  (*PUBL(free))(void *) = free;
PCRE_EXP_DATA_DEFN void *(*PUBL(stack_malloc))(size_t) = malloc;
PCRE_EXP_DATA_DEFN void  (*PUBL(stack_free))(void *) = free;
PCRE_EXP_DATA_DEFN int   (*PUBL(callout))(PUBL(callout_block) *) = NULL;
PCRE_EXP_DATA_DEFN int   (*PUBL(stack_guard))(void) = NULL;
#endif

/* End of pcre_globals.c */
