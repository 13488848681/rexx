
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

/* Generate code with 32 bit character support. */
#define COMPILE_PCRE32

#include "pcre_internal.h"

int
PRIV(valid_utf)(PCRE_PUCHAR string, int length, int *erroroffset)
{
#ifdef SUPPORT_UTF
register PCRE_PUCHAR p;
register pcre_uchar c;

if (length < 0)
  {
  for (p = string; *p != 0; p++);
  length = p - string;
  }

for (p = string; length-- > 0; p++)
  {
  c = *p;

  if ((c & 0xfffff800u) != 0xd800u)
    {
    /* Normal UTF-32 code point. Neither high nor low surrogate. */
    if (c > 0x10ffffu)
      {
      *erroroffset = p - string;
      return PCRE_UTF32_ERR3;
      }
    }
  else
    {
    /* A surrogate */
    *erroroffset = p - string;
    return PCRE_UTF32_ERR1;
    }
  }

#else  /* SUPPORT_UTF */
(void)(string);  /* Keep picky compilers happy */
(void)(length);
(void)(erroroffset);
#endif /* SUPPORT_UTF */

return PCRE_UTF32_ERR0;   /* This indicates success */
}

/* End of pcre32_valid_utf32.c */
