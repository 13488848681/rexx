
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "pcre_internal.h"


/*************************************************
*          Return version string                 *
*************************************************/

/* These macros are the standard way of turning unquoted text into C strings.
They allow macros like PCRE_MAJOR to be defined without quotes, which is
convenient for user programs that want to test its value. */

#define STRING(a)  # a
#define XSTRING(s) STRING(s)

/* A problem turned up with PCRE_PRERELEASE, which is defined empty for
production releases. Originally, it was used naively in this code:

  return XSTRING(PCRE_MAJOR)
         "." XSTRING(PCRE_MINOR)
             XSTRING(PCRE_PRERELEASE)
         " " XSTRING(PCRE_DATE);

However, when PCRE_PRERELEASE is empty, this leads to an attempted expansion of
STRING(). The C standard states: "If (before argument substitution) any
argument consists of no preprocessing tokens, the behavior is undefined." It
turns out the gcc treats this case as a single empty string - which is what we
really want - but Visual C grumbles about the lack of an argument for the
macro. Unfortunately, both are within their rights. To cope with both ways of
handling this, I had resort to some messy hackery that does a test at run time.
I could find no way of detecting that a macro is defined as an empty string at
pre-processor time. This hack uses a standard trick for avoiding calling
the STRING macro with an empty argument when doing the test. */

#if defined COMPILE_PCRE8
PCRE_EXP_DEFN const char * PCRE_CALL_CONVENTION
pcre_version(void)
#elif defined COMPILE_PCRE16
PCRE_EXP_DEFN const char * PCRE_CALL_CONVENTION
pcre16_version(void)
#elif defined COMPILE_PCRE32
PCRE_EXP_DEFN const char * PCRE_CALL_CONVENTION
pcre32_version(void)
#endif
{
return (XSTRING(Z PCRE_PRERELEASE)[1] == 0)?
  XSTRING(PCRE_MAJOR.PCRE_MINOR PCRE_DATE) :
  XSTRING(PCRE_MAJOR.PCRE_MINOR) XSTRING(PCRE_PRERELEASE PCRE_DATE);
}

/* End of pcre_version.c */
