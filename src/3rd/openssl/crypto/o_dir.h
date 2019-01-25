

#ifndef O_DIR_H
# define O_DIR_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OPENSSL_dir_context_st OPENSSL_DIR_CTX;

  /*
   * returns NULL on error or end-of-directory. If it is end-of-directory,
   * errno will be zero
   */
const char *OPENSSL_DIR_read(OPENSSL_DIR_CTX **ctx, const char *directory);
  /* returns 1 on success, 0 on error */
int OPENSSL_DIR_end(OPENSSL_DIR_CTX **ctx);

#ifdef __cplusplus
}
#endif

#endif                          /* LPDIR_H */
