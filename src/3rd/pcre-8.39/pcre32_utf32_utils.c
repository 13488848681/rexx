
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

/* Generate code with 32 bit character support. */
#define COMPILE_PCRE32

#include "pcre_internal.h"

#ifdef SUPPORT_UTF
static pcre_uint32
swap_uint32(pcre_uint32 value)
{
return ((value & 0x000000ff) << 24) |
       ((value & 0x0000ff00) <<  8) |
       ((value & 0x00ff0000) >>  8) |
       (value >> 24);
}
#endif

int
pcre32_utf32_to_host_byte_order(PCRE_UCHAR32 *output, PCRE_SPTR32 input,
  int length, int *host_byte_order, int keep_boms)
{
#ifdef SUPPORT_UTF
/* This function converts any UTF-32 string to host byte order and optionally
removes any Byte Order Marks (BOMS). Returns with the remainig length. */
int host_bo = host_byte_order != NULL ? *host_byte_order : 1;
pcre_uchar *optr = (pcre_uchar *)output;
const pcre_uchar *iptr = (const pcre_uchar *)input;
const pcre_uchar *end;
/* The c variable must be unsigned. */
register pcre_uchar c;

if (length < 0)
  end = iptr + STRLEN_UC(iptr) + 1;
else
  end = iptr + length;

while (iptr < end)
  {
  c = *iptr++;
  if (c == 0x0000feffu || c == 0xfffe0000u)
    {
    /* Detecting the byte order of the machine is unnecessary, it is
    enough to know that the UTF-32 string has the same byte order or not. */
    host_bo = c == 0x0000feffu;
    if (keep_boms != 0)
      *optr++ = 0x0000feffu;
    }
  else
    *optr++ = host_bo ? c : swap_uint32(c);
  }
if (host_byte_order != NULL)
  *host_byte_order = host_bo;

#else /* SUPPORT_UTF */
(void)(output);  /* Keep picky compilers happy */
(void)(input);
(void)(keep_boms);
(void)(host_byte_order);
#endif /* SUPPORT_UTF */
return length;
}

/* End of pcre32_utf32_utils.c */
