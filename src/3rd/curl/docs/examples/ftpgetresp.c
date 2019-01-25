
#include <stdio.h>

#include <curl/curl.h>

/* <DESC>
 * Similar to ftpget.c but also stores the received response-lines
 * in a separate file using our own callback!
 * </DESC>
 */
static size_t
write_response(void *ptr, size_t size, size_t nmemb, void *data)
{
  FILE *writehere = (FILE *)data;
  return fwrite(ptr, size, nmemb, writehere);
}

int main(void)
{
  CURL *curl;
  CURLcode res;
  FILE *ftpfile;
  FILE *respfile;

  /* local file name to store the file as */
  ftpfile = fopen("ftp-list", "wb"); /* b is binary, needed on win32 */

  /* local file name to store the FTP server's response lines in */
  respfile = fopen("ftp-responses", "wb"); /* b is binary, needed on win32 */

  curl = curl_easy_init();
  if(curl) {
    /* Get a file listing from sunet */
    curl_easy_setopt(curl, CURLOPT_URL, "ftp://ftp.example.com/");
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, ftpfile);
    /* If you intend to use this on windows with a libcurl DLL, you must use
       CURLOPT_WRITEFUNCTION as well */
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, write_response);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, respfile);
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);
  }

  fclose(ftpfile); /* close the local file */
  fclose(respfile); /* close the response file */

  return 0;
}
