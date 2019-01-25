
#include "eng_int.h"

/*
 * If this symbol is defined then ENGINE_get_default_ECDH(), the function
 * that is used by ECDH to hook in implementation code and cache defaults
 * (etc), will display brief debugging summaries to stderr with the 'nid'.
 */
/* #define ENGINE_ECDH_DEBUG */

static ENGINE_TABLE *ecdh_table = NULL;
static const int dummy_nid = 1;

void ENGINE_unregister_ECDH(ENGINE *e)
{
    engine_table_unregister(&ecdh_table, e);
}

static void engine_unregister_all_ECDH(void)
{
    engine_table_cleanup(&ecdh_table);
}

int ENGINE_register_ECDH(ENGINE *e)
{
    if (e->ecdh_meth)
        return engine_table_register(&ecdh_table,
                                     engine_unregister_all_ECDH, e,
                                     &dummy_nid, 1, 0);
    return 1;
}

void ENGINE_register_all_ECDH()
{
    ENGINE *e;

    for (e = ENGINE_get_first(); e; e = ENGINE_get_next(e))
        ENGINE_register_ECDH(e);
}

int ENGINE_set_default_ECDH(ENGINE *e)
{
    if (e->ecdh_meth)
        return engine_table_register(&ecdh_table,
                                     engine_unregister_all_ECDH, e,
                                     &dummy_nid, 1, 1);
    return 1;
}

/*
 * Exposed API function to get a functional reference from the implementation
 * table (ie. try to get a functional reference from the tabled structural
 * references).
 */
ENGINE *ENGINE_get_default_ECDH(void)
{
    return engine_table_select(&ecdh_table, dummy_nid);
}

/* Obtains an ECDH implementation from an ENGINE functional reference */
const ECDH_METHOD *ENGINE_get_ECDH(const ENGINE *e)
{
    return e->ecdh_meth;
}

/* Sets an ECDH implementation in an ENGINE structure */
int ENGINE_set_ECDH(ENGINE *e, const ECDH_METHOD *ecdh_meth)
{
    e->ecdh_meth = ecdh_meth;
    return 1;
}
