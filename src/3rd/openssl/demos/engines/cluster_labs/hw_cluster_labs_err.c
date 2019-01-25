
#include <stdio.h>
#include <openssl/err.h>
#include "hw_cluster_labs_err.h"

/* BEGIN ERROR CODES */
#ifndef OPENSSL_NO_ERR
static ERR_STRING_DATA CL_str_functs[] = {
    {ERR_PACK(0, CL_F_CLUSTER_LABS_CTRL, 0), "CLUSTER_LABS_CTRL"},
    {ERR_PACK(0, CL_F_CLUSTER_LABS_DSA_SIGN, 0), "CLUSTER_LABS_DSA_SIGN"},
    {ERR_PACK(0, CL_F_CLUSTER_LABS_DSA_VERIFY, 0), "CLUSTER_LABS_DSA_VERIFY"},
    {ERR_PACK(0, CL_F_CLUSTER_LABS_FINISH, 0), "CLUSTER_LABS_FINISH"},
    {ERR_PACK(0, CL_F_CLUSTER_LABS_INIT, 0), "CLUSTER_LABS_INIT"},
    {ERR_PACK(0, CL_F_CLUSTER_LABS_MOD_EXP, 0), "CLUSTER_LABS_MOD_EXP"},
    {ERR_PACK(0, CL_F_CLUSTER_LABS_MOD_EXP_CRT, 0),
     "CLUSTER_LABS_MOD_EXP_CRT"},
    {ERR_PACK(0, CL_F_CLUSTER_LABS_RAND_BYTES, 0), "CLUSTER_LABS_RAND_BYTES"},
    {ERR_PACK(0, CL_F_CLUSTER_LABS_RSA_MOD_EXP, 0),
     "CLUSTER_LABS_RSA_MOD_EXP"},
    {ERR_PACK(0, CL_F_CLUSTER_LABS_RSA_PRIV_DEC, 0),
     "CLUSTER_LABS_RSA_PRIV_DEC"},
    {ERR_PACK(0, CL_F_CLUSTER_LABS_RSA_PRIV_ENC, 0),
     "CLUSTER_LABS_RSA_PRIV_ENC"},
    {ERR_PACK(0, CL_F_CLUSTER_LABS_RSA_PUB_DEC, 0),
     "CLUSTER_LABS_RSA_PUB_DEC"},
    {ERR_PACK(0, CL_F_CLUSTER_LABS_RSA_PUB_ENC, 0),
     "CLUSTER_LABS_RSA_PUB_ENC"},
    {0, NULL}
};

static ERR_STRING_DATA CL_str_reasons[] = {
    {CL_R_ALREADY_LOADED, "already loaded"},
    {CL_R_COMMAND_NOT_IMPLEMENTED, "command not implemented"},
    {CL_R_DSO_FAILURE, "dso failure"},
    {CL_R_FUNCTION_NOT_BINDED, "function not binded"},
    {CL_R_INIT_FAILED, "init failed"},
    {CL_R_NOT_LOADED, "not loaded"},
    {0, NULL}
};

#endif

#ifdef CL_LIB_NAME
static ERR_STRING_DATA CL_lib_name[] = {
    {0, CL_LIB_NAME},
    {0, NULL}
};
#endif

static int CL_lib_error_code = 0;
static int CL_error_init = 1;

static void ERR_load_CL_strings(void)
{
    if (CL_lib_error_code == 0)
        CL_lib_error_code = ERR_get_next_error_library();

    if (CL_error_init) {
        CL_error_init = 0;
#ifndef OPENSSL_NO_ERR
        ERR_load_strings(CL_lib_error_code, CL_str_functs);
        ERR_load_strings(CL_lib_error_code, CL_str_reasons);
#endif

#ifdef CL_LIB_NAME
        CL_lib_name->error = ERR_PACK(CL_lib_error_code, 0, 0);
        ERR_load_strings(0, CL_lib_name);
#endif
    }
}

static void ERR_unload_CL_strings(void)
{
    if (CL_error_init == 0) {
#ifndef OPENSSL_NO_ERR
        ERR_unload_strings(CL_lib_error_code, CL_str_functs);
        ERR_unload_strings(CL_lib_error_code, CL_str_reasons);
#endif

#ifdef CL_LIB_NAME
        ERR_unload_strings(0, CL_lib_name);
#endif
        CL_error_init = 1;
    }
}

static void ERR_CL_error(int function, int reason, char *file, int line)
{
    if (CL_lib_error_code == 0)
        CL_lib_error_code = ERR_get_next_error_library();
    ERR_PUT_error(CL_lib_error_code, function, reason, file, line);
}
