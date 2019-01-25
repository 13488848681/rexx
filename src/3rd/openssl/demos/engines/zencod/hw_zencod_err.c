
#include <stdio.h>
#include <openssl/err.h>
#include "hw_zencod_err.h"

/* BEGIN ERROR CODES */
#ifndef OPENSSL_NO_ERR
static ERR_STRING_DATA ZENCOD_str_functs[] = {
    {ERR_PACK(0, ZENCOD_F_ZENCOD_BN_MOD_EXP, 0), "ZENCOD_BN_MOD_EXP"},
    {ERR_PACK(0, ZENCOD_F_ZENCOD_CTRL, 0), "ZENCOD_CTRL"},
    {ERR_PACK(0, ZENCOD_F_ZENCOD_DH_COMPUTE, 0), "ZENCOD_DH_COMPUTE"},
    {ERR_PACK(0, ZENCOD_F_ZENCOD_DH_GENERATE, 0), "ZENCOD_DH_GENERATE"},
    {ERR_PACK(0, ZENCOD_F_ZENCOD_DSA_DO_SIGN, 0), "ZENCOD_DSA_DO_SIGN"},
    {ERR_PACK(0, ZENCOD_F_ZENCOD_DSA_DO_VERIFY, 0), "ZENCOD_DSA_DO_VERIFY"},
    {ERR_PACK(0, ZENCOD_F_ZENCOD_FINISH, 0), "ZENCOD_FINISH"},
    {ERR_PACK(0, ZENCOD_F_ZENCOD_INIT, 0), "ZENCOD_INIT"},
    {ERR_PACK(0, ZENCOD_F_ZENCOD_RAND, 0), "ZENCOD_RAND"},
    {ERR_PACK(0, ZENCOD_F_ZENCOD_RSA_MOD_EXP, 0), "ZENCOD_RSA_MOD_EXP"},
    {ERR_PACK(0, ZENCOD_F_ZENCOD_RSA_MOD_EXP_CRT, 0),
     "ZENCOD_RSA_MOD_EXP_CRT"},
    {0, NULL}
};

static ERR_STRING_DATA ZENCOD_str_reasons[] = {
    {ZENCOD_R_ALREADY_LOADED, "already loaded"},
    {ZENCOD_R_BAD_KEY_COMPONENTS, "bad key components"},
    {ZENCOD_R_BN_EXPAND_FAIL, "bn expand fail"},
    {ZENCOD_R_CTRL_COMMAND_NOT_IMPLEMENTED, "ctrl command not implemented"},
    {ZENCOD_R_DSO_FAILURE, "dso failure"},
    {ZENCOD_R_NOT_LOADED, "not loaded"},
    {ZENCOD_R_REQUEST_FAILED, "request failed"},
    {ZENCOD_R_UNIT_FAILURE, "unit failure"},
    {0, NULL}
};

#endif

#ifdef ZENCOD_LIB_NAME
static ERR_STRING_DATA ZENCOD_lib_name[] = {
    {0, ZENCOD_LIB_NAME},
    {0, NULL}
};
#endif

static int ZENCOD_lib_error_code = 0;
static int ZENCOD_error_init = 1;

static void ERR_load_ZENCOD_strings(void)
{
    if (ZENCOD_lib_error_code == 0)
        ZENCOD_lib_error_code = ERR_get_next_error_library();

    if (ZENCOD_error_init) {
        ZENCOD_error_init = 0;
#ifndef OPENSSL_NO_ERR
        ERR_load_strings(ZENCOD_lib_error_code, ZENCOD_str_functs);
        ERR_load_strings(ZENCOD_lib_error_code, ZENCOD_str_reasons);
#endif

#ifdef ZENCOD_LIB_NAME
        ZENCOD_lib_name->error = ERR_PACK(ZENCOD_lib_error_code, 0, 0);
        ERR_load_strings(0, ZENCOD_lib_name);
#endif
    }
}

static void ERR_unload_ZENCOD_strings(void)
{
    if (ZENCOD_error_init == 0) {
#ifndef OPENSSL_NO_ERR
        ERR_unload_strings(ZENCOD_lib_error_code, ZENCOD_str_functs);
        ERR_unload_strings(ZENCOD_lib_error_code, ZENCOD_str_reasons);
#endif

#ifdef ZENCOD_LIB_NAME
        ERR_unload_strings(0, ZENCOD_lib_name);
#endif
        ZENCOD_error_init = 1;
    }
}

static void ERR_ZENCOD_error(int function, int reason, char *file, int line)
{
    if (ZENCOD_lib_error_code == 0)
        ZENCOD_lib_error_code = ERR_get_next_error_library();
    ERR_PUT_error(ZENCOD_lib_error_code, function, reason, file, line);
}
