
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#define COMPILE_PCRE8

#include "pcre_internal.h"

unsigned
int
PRIV(ord2utf)(pcre_uint32 cvalue, pcre_uchar *buffer)
{
#ifdef SUPPORT_UTF

register int i, j;

for (i = 0; i < PRIV(utf8_table1_size); i++)
  if ((int)cvalue <= PRIV(utf8_table1)[i]) break;
buffer += i;
for (j = i; j > 0; j--)
 {
 *buffer-- = 0x80 | (cvalue & 0x3f);
 cvalue >>= 6;
 }
*buffer = PRIV(utf8_table2)[i] | cvalue;
return i + 1;

#else

(void)(cvalue);  /* Keep compiler happy; this function won't ever be */
(void)(buffer);  /* called when SUPPORT_UTF is not defined. */
return 0;

#endif
}

/* End of pcre_ord2utf8.c */
