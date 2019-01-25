
#ifndef HEADER_STORE_LOCL_H
# define HEADER_STORE_LOCL_H

# include <openssl/crypto.h>
# include <openssl/store.h>

#ifdef  __cplusplus
extern "C" {
#endif

struct store_method_st {
    char *name;
    /*
     * All the functions return a positive integer or non-NULL for success
     * and 0, a negative integer or NULL for failure
     */
    /* Initialise the STORE with private data */
    STORE_INITIALISE_FUNC_PTR init;
    /* Initialise the STORE with private data */
    STORE_CLEANUP_FUNC_PTR clean;
    /* Generate an object of a given type */
    STORE_GENERATE_OBJECT_FUNC_PTR generate_object;
    /*
     * Get an object of a given type.  This function isn't really very useful
     * since the listing functions (below) can be used for the same purpose
     * and are much more general.
     */
    STORE_GET_OBJECT_FUNC_PTR get_object;
    /* Store an object of a given type. */
    STORE_STORE_OBJECT_FUNC_PTR store_object;
    /* Modify the attributes bound to an object of a given type. */
    STORE_MODIFY_OBJECT_FUNC_PTR modify_object;
    /* Revoke an object of a given type. */
    STORE_HANDLE_OBJECT_FUNC_PTR revoke_object;
    /* Delete an object of a given type. */
    STORE_HANDLE_OBJECT_FUNC_PTR delete_object;
    /*
     * List a bunch of objects of a given type and with the associated
     * attributes.
     */
    STORE_START_OBJECT_FUNC_PTR list_object_start;
    STORE_NEXT_OBJECT_FUNC_PTR list_object_next;
    STORE_END_OBJECT_FUNC_PTR list_object_end;
    STORE_END_OBJECT_FUNC_PTR list_object_endp;
    /* Store-level function to make any necessary update operations. */
    STORE_GENERIC_FUNC_PTR update_store;
    /* Store-level function to get exclusive access to the store. */
    STORE_GENERIC_FUNC_PTR lock_store;
    /* Store-level function to release exclusive access to the store. */
    STORE_GENERIC_FUNC_PTR unlock_store;
    /* Generic control function */
    STORE_CTRL_FUNC_PTR ctrl;
};

struct store_st {
    const STORE_METHOD *meth;
    /* functional reference if 'meth' is ENGINE-provided */
    ENGINE *engine;
    CRYPTO_EX_DATA ex_data;
    int references;
};
#ifdef  __cplusplus
}
#endif

#endif
