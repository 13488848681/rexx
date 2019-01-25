
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "pcre_internal.h"

BOOL
PRIV(is_newline)(PCRE_PUCHAR ptr, int type, PCRE_PUCHAR endptr, int *lenptr,
  BOOL utf)
{
pcre_uint32 c;
(void)utf;
#ifdef SUPPORT_UTF
if (utf)
  {
  GETCHAR(c, ptr);
  }
else
#endif  /* SUPPORT_UTF */
  c = *ptr;

/* Note that this function is called only for ANY or ANYCRLF. */

if (type == NLTYPE_ANYCRLF) switch(c)
  {
  case CHAR_LF: *lenptr = 1; return TRUE;
  case CHAR_CR: *lenptr = (ptr < endptr - 1 && ptr[1] == CHAR_LF)? 2 : 1;
               return TRUE;
  default: return FALSE;
  }

/* NLTYPE_ANY */

else switch(c)
  {
#ifdef EBCDIC
  case CHAR_NEL:
#endif
  case CHAR_LF:
  case CHAR_VT:
  case CHAR_FF: *lenptr = 1; return TRUE;

  case CHAR_CR:
  *lenptr = (ptr < endptr - 1 && ptr[1] == CHAR_LF)? 2 : 1;
  return TRUE;

#ifndef EBCDIC
#ifdef COMPILE_PCRE8
  case CHAR_NEL: *lenptr = utf? 2 : 1; return TRUE;
  case 0x2028:                                       /* LS */
  case 0x2029: *lenptr = 3; return TRUE;             /* PS */
#else /* COMPILE_PCRE16 || COMPILE_PCRE32 */
  case CHAR_NEL:
  case 0x2028:                                       /* LS */
  case 0x2029: *lenptr = 1; return TRUE;             /* PS */
#endif  /* COMPILE_PCRE8 */
#endif  /* Not EBCDIC */

  default: return FALSE;
  }
}



/*************************************************
*     Check for newline at previous position     *
*************************************************/

/* It is guaranteed that the initial value of ptr is greater than the start of
the string that is being processed.

Arguments:
  ptr          pointer to possible newline
  type         the newline type
  startptr     pointer to the start of the string
  lenptr       where to return the length
  utf          TRUE if in utf mode

Returns:       TRUE or FALSE
*/

BOOL
PRIV(was_newline)(PCRE_PUCHAR ptr, int type, PCRE_PUCHAR startptr, int *lenptr,
  BOOL utf)
{
pcre_uint32 c;
(void)utf;
ptr--;
#ifdef SUPPORT_UTF
if (utf)
  {
  BACKCHAR(ptr);
  GETCHAR(c, ptr);
  }
else
#endif  /* SUPPORT_UTF */
  c = *ptr;

/* Note that this function is called only for ANY or ANYCRLF. */

if (type == NLTYPE_ANYCRLF) switch(c)
  {
  case CHAR_LF:
  *lenptr = (ptr > startptr && ptr[-1] == CHAR_CR)? 2 : 1;
  return TRUE;

  case CHAR_CR: *lenptr = 1; return TRUE;
  default: return FALSE;
  }

/* NLTYPE_ANY */

else switch(c)
  {
  case CHAR_LF:
  *lenptr = (ptr > startptr && ptr[-1] == CHAR_CR)? 2 : 1;
  return TRUE;

#ifdef EBCDIC
  case CHAR_NEL:
#endif
  case CHAR_VT:
  case CHAR_FF:
  case CHAR_CR: *lenptr = 1; return TRUE;

#ifndef EBCDIC
#ifdef COMPILE_PCRE8
  case CHAR_NEL: *lenptr = utf? 2 : 1; return TRUE;
  case 0x2028:                                       /* LS */
  case 0x2029: *lenptr = 3; return TRUE;             /* PS */
#else /* COMPILE_PCRE16 || COMPILE_PCRE32 */
  case CHAR_NEL:
  case 0x2028:                                       /* LS */
  case 0x2029: *lenptr = 1; return TRUE;             /* PS */
#endif  /* COMPILE_PCRE8 */
#endif  /* NotEBCDIC */

  default: return FALSE;
  }
}

/* End of pcre_newline.c */
