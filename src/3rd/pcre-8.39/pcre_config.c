
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

/* Keep the original link size. */
static int real_link_size = LINK_SIZE;

#include "pcre_internal.h"

#if defined COMPILE_PCRE8
PCRE_EXP_DEFN int PCRE_CALL_CONVENTION
pcre_config(int what, void *where)
#elif defined COMPILE_PCRE16
PCRE_EXP_DEFN int PCRE_CALL_CONVENTION
pcre16_config(int what, void *where)
#elif defined COMPILE_PCRE32
PCRE_EXP_DEFN int PCRE_CALL_CONVENTION
pcre32_config(int what, void *where)
#endif
{
switch (what)
  {
  case PCRE_CONFIG_UTF8:
#if defined COMPILE_PCRE16 || defined COMPILE_PCRE32
  *((int *)where) = 0;
  return PCRE_ERROR_BADOPTION;
#else
#if defined SUPPORT_UTF
  *((int *)where) = 1;
#else
  *((int *)where) = 0;
#endif
  break;
#endif

  case PCRE_CONFIG_UTF16:
#if defined COMPILE_PCRE8 || defined COMPILE_PCRE32
  *((int *)where) = 0;
  return PCRE_ERROR_BADOPTION;
#else
#if defined SUPPORT_UTF
  *((int *)where) = 1;
#else
  *((int *)where) = 0;
#endif
  break;
#endif

  case PCRE_CONFIG_UTF32:
#if defined COMPILE_PCRE8 || defined COMPILE_PCRE16
  *((int *)where) = 0;
  return PCRE_ERROR_BADOPTION;
#else
#if defined SUPPORT_UTF
  *((int *)where) = 1;
#else
  *((int *)where) = 0;
#endif
  break;
#endif

  case PCRE_CONFIG_UNICODE_PROPERTIES:
#ifdef SUPPORT_UCP
  *((int *)where) = 1;
#else
  *((int *)where) = 0;
#endif
  break;

  case PCRE_CONFIG_JIT:
#ifdef SUPPORT_JIT
  *((int *)where) = 1;
#else
  *((int *)where) = 0;
#endif
  break;

  case PCRE_CONFIG_JITTARGET:
#ifdef SUPPORT_JIT
  *((const char **)where) = PRIV(jit_get_target)();
#else
  *((const char **)where) = NULL;
#endif
  break;

  case PCRE_CONFIG_NEWLINE:
  *((int *)where) = NEWLINE;
  break;

  case PCRE_CONFIG_BSR:
#ifdef BSR_ANYCRLF
  *((int *)where) = 1;
#else
  *((int *)where) = 0;
#endif
  break;

  case PCRE_CONFIG_LINK_SIZE:
  *((int *)where) = real_link_size;
  break;

  case PCRE_CONFIG_POSIX_MALLOC_THRESHOLD:
  *((int *)where) = POSIX_MALLOC_THRESHOLD;
  break;

  case PCRE_CONFIG_PARENS_LIMIT:
  *((unsigned long int *)where) = PARENS_NEST_LIMIT;
  break;

  case PCRE_CONFIG_MATCH_LIMIT:
  *((unsigned long int *)where) = MATCH_LIMIT;
  break;

  case PCRE_CONFIG_MATCH_LIMIT_RECURSION:
  *((unsigned long int *)where) = MATCH_LIMIT_RECURSION;
  break;

  case PCRE_CONFIG_STACKRECURSE:
#ifdef NO_RECURSE
  *((int *)where) = 0;
#else
  *((int *)where) = 1;
#endif
  break;

  default: return PCRE_ERROR_BADOPTION;
  }

return 0;
}

/* End of pcre_config.c */
