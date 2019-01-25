
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

/* Generate code with 32 bit character support. */
#define COMPILE_PCRE32

#include "pcre_internal.h"

unsigned int
PRIV(ord2utf)(pcre_uint32 cvalue, pcre_uchar *buffer)
{
#ifdef SUPPORT_UTF

*buffer = (pcre_uchar)cvalue;
return 1;

#else /* SUPPORT_UTF */
(void)(cvalue);  /* Keep compiler happy; this function won't ever be */
(void)(buffer);  /* called when SUPPORT_UTF is not defined. */
return 0;
#endif /* SUPPORT_UTF */
}

/* End of pcre32_ord2utf32.c */
