
#ifndef PCRECPP_INTERNAL_H
#define PCRECPP_INTERNAL_H

#ifndef PCRECPP_EXP_DECL
#  ifdef _WIN32
#    ifndef PCRE_STATIC
#      define PCRECPP_EXP_DECL       extern __declspec(dllexport)
#      define PCRECPP_EXP_DEFN       __declspec(dllexport)
#    else
#      define PCRECPP_EXP_DECL       extern
#      define PCRECPP_EXP_DEFN
#    endif
#  else
#    define PCRECPP_EXP_DECL         extern
#    define PCRECPP_EXP_DEFN
#  endif
#endif

#endif  /* PCRECPP_INTERNAL_H */

/* End of pcrecpp_internal.h */
