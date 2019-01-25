
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

/* Generate code with 16 bit character support. */
#define COMPILE_PCRE16

#include "pcre_internal.h"


int
pcre16_utf16_to_host_byte_order(PCRE_UCHAR16 *output, PCRE_SPTR16 input,
  int length, int *host_byte_order, int keep_boms)
{
#ifdef SUPPORT_UTF
/* This function converts any UTF-16 string to host byte order and optionally
removes any Byte Order Marks (BOMS). Returns with the remainig length. */
int host_bo = host_byte_order != NULL ? *host_byte_order : 1;
pcre_uchar *optr = (pcre_uchar *)output;
const pcre_uchar *iptr = (const pcre_uchar *)input;
const pcre_uchar *end;
/* The c variable must be unsigned. */
register pcre_uchar c;

if (length < 0)
  length = STRLEN_UC(iptr) + 1;
end = iptr + length;

while (iptr < end)
  {
  c = *iptr++;
  if (c == 0xfeff || c == 0xfffe)
    {
    /* Detecting the byte order of the machine is unnecessary, it is
    enough to know that the UTF-16 string has the same byte order or not. */
    host_bo = c == 0xfeff;
    if (keep_boms != 0)
      *optr++ = 0xfeff;
    else
      length--;
    }
  else
    *optr++ = host_bo ? c : ((c >> 8) | (c << 8)); /* Flip bytes if needed. */
  }
if (host_byte_order != NULL)
  *host_byte_order = host_bo;

#else /* Not SUPPORT_UTF */
(void)(output);  /* Keep picky compilers happy */
(void)(input);
(void)(keep_boms);
(void)(host_byte_order);
#endif /* SUPPORT_UTF */
return length;
}

/* End of pcre16_utf16_utils.c */
