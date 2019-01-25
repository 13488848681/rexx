
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>
#include "pcrecpp_internal.h"
#include "pcre_stringpiece.h"

std::ostream& operator<<(std::ostream& o, const pcrecpp::StringPiece& piece) {
  return (o << piece.as_string());
}
