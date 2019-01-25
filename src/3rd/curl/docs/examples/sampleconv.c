
#include <stdio.h>
#include <curl/curl.h>

CURLcode my_conv_from_ascii_to_ebcdic(char *buffer, size_t length)
{
    char *tempptrin, *tempptrout;
    size_t bytes = length;
    int rc;
    tempptrin = tempptrout = buffer;
    rc = platform_a2e(&tempptrin, &bytes, &tempptrout, &bytes);
    if (rc == PLATFORM_CONV_OK) {
      return(CURLE_OK);
    } else {
      return(CURLE_CONV_FAILED);
    }
}

CURLcode my_conv_from_ebcdic_to_ascii(char *buffer, size_t length)
{
    char *tempptrin, *tempptrout;
    size_t bytes = length;
    int rc;
    tempptrin = tempptrout = buffer;
    rc = platform_e2a(&tempptrin, &bytes, &tempptrout, &bytes);
    if (rc == PLATFORM_CONV_OK) {
      return(CURLE_OK);
    } else {
      return(CURLE_CONV_FAILED);
    }
}

CURLcode my_conv_from_utf8_to_ebcdic(char *buffer, size_t length)
{
    char *tempptrin, *tempptrout;
    size_t bytes = length;
    int rc;
    tempptrin = tempptrout = buffer;
    rc = platform_u2e(&tempptrin, &bytes, &tempptrout, &bytes);
    if (rc == PLATFORM_CONV_OK) {
      return(CURLE_OK);
    } else {
      return(CURLE_CONV_FAILED);
    }
}

int main(void)
{
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");

    /* use platform-specific functions for codeset conversions */
    curl_easy_setopt(curl, CURLOPT_CONV_FROM_NETWORK_FUNCTION,
                     my_conv_from_ascii_to_ebcdic);
    curl_easy_setopt(curl, CURLOPT_CONV_TO_NETWORK_FUNCTION,
                     my_conv_from_ebcdic_to_ascii);
    curl_easy_setopt(curl, CURLOPT_CONV_FROM_UTF8_FUNCTION,
                     my_conv_from_utf8_to_ebcdic);

    res = curl_easy_perform(curl);

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  return 0;
}
