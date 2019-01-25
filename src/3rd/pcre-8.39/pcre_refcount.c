
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "pcre_internal.h"

#if defined COMPILE_PCRE8
PCRE_EXP_DEFN int PCRE_CALL_CONVENTION
pcre_refcount(pcre *argument_re, int adjust)
#elif defined COMPILE_PCRE16
PCRE_EXP_DEFN int PCRE_CALL_CONVENTION
pcre16_refcount(pcre16 *argument_re, int adjust)
#elif defined COMPILE_PCRE32
PCRE_EXP_DEFN int PCRE_CALL_CONVENTION
pcre32_refcount(pcre32 *argument_re, int adjust)
#endif
{
REAL_PCRE *re = (REAL_PCRE *)argument_re;
if (re == NULL) return PCRE_ERROR_NULL;
if (re->magic_number != MAGIC_NUMBER) return PCRE_ERROR_BADMAGIC;
if ((re->flags & PCRE_MODE) == 0) return PCRE_ERROR_BADMODE;
re->ref_count = (-adjust > re->ref_count)? 0 :
                (adjust + re->ref_count > 65535)? 65535 :
                re->ref_count + adjust;
return re->ref_count;
}

/* End of pcre_refcount.c */
