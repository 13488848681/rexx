
#include <stdio.h>
#include "cryptlib.h"
#include <openssl/dso.h>

static DSO_METHOD dso_meth_null = {
    "NULL shared library method",
    NULL,                       /* load */
    NULL,                       /* unload */
    NULL,                       /* bind_var */
    NULL,                       /* bind_func */
/* For now, "unbind" doesn't exist */
#if 0
    NULL,                       /* unbind_var */
    NULL,                       /* unbind_func */
#endif
    NULL,                       /* ctrl */
    NULL,                       /* dso_name_converter */
    NULL,                       /* dso_merger */
    NULL,                       /* init */
    NULL,                       /* finish */
    NULL,                       /* pathbyaddr */
    NULL                        /* globallookup */
};

DSO_METHOD *DSO_METHOD_null(void)
{
    return (&dso_meth_null);
}
