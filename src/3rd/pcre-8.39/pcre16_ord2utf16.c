
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

/* Generate code with 16 bit character support. */
#define COMPILE_PCRE16

#include "pcre_internal.h"

/*************************************************
*       Convert character value to UTF-16         *
*************************************************/

/* This function takes an integer value in the range 0 - 0x10ffff
and encodes it as a UTF-16 character in 1 to 2 pcre_uchars.

Arguments:
  cvalue     the character value
  buffer     pointer to buffer for result - at least 2 pcre_uchars long

Returns:     number of characters placed in the buffer
*/

unsigned int
PRIV(ord2utf)(pcre_uint32 cvalue, pcre_uchar *buffer)
{
#ifdef SUPPORT_UTF

if (cvalue <= 0xffff)
  {
  *buffer = (pcre_uchar)cvalue;
  return 1;
  }

cvalue -= 0x10000;
*buffer++ = 0xd800 | (cvalue >> 10);
*buffer = 0xdc00 | (cvalue & 0x3ff);
return 2;

#else /* SUPPORT_UTF */
(void)(cvalue);  /* Keep compiler happy; this function won't ever be */
(void)(buffer);  /* called when SUPPORT_UTF is not defined. */
return 0;
#endif /* SUPPORT_UTF */
}

/* End of pcre16_ord2utf16.c */
