

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

/* Generate code with 16 bit character support. */
#define COMPILE_PCRE16

#include "pcre_internal.h"

int
PRIV(valid_utf)(PCRE_PUCHAR string, int length, int *erroroffset)
{
#ifdef SUPPORT_UTF
register PCRE_PUCHAR p;
register pcre_uint32 c;

if (length < 0)
  {
  for (p = string; *p != 0; p++);
  length = p - string;
  }

for (p = string; length-- > 0; p++)
  {
  c = *p;

  if ((c & 0xf800) != 0xd800)
    {
    /* Normal UTF-16 code point. Neither high nor low surrogate. */
    }
  else if ((c & 0x0400) == 0)
    {
    /* High surrogate. Must be a followed by a low surrogate. */
    if (length == 0)
      {
      *erroroffset = p - string;
      return PCRE_UTF16_ERR1;
      }
    p++;
    length--;
    if ((*p & 0xfc00) != 0xdc00)
      {
      *erroroffset = p - string;
      return PCRE_UTF16_ERR2;
      }
    }
  else
    {
    /* Isolated low surrogate. Always an error. */
    *erroroffset = p - string;
    return PCRE_UTF16_ERR3;
    }
  }

#else  /* SUPPORT_UTF */
(void)(string);  /* Keep picky compilers happy */
(void)(length);
(void)(erroroffset);
#endif /* SUPPORT_UTF */

return PCRE_UTF16_ERR0;   /* This indicates success */
}

/* End of pcre16_valid_utf16.c */
