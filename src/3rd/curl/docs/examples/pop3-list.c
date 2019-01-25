
#include <stdio.h>
#include <curl/curl.h>

/* This is a simple example using libcurl's POP3 capabilities to list the
 * contents of a mailbox.
 *
 * Note that this example requires libcurl 7.20.0 or above.
 */

int main(void)
{
  CURL *curl;
  CURLcode res = CURLE_OK;

  curl = curl_easy_init();
  if(curl) {
    /* Set username and password */
    curl_easy_setopt(curl, CURLOPT_USERNAME, "user");
    curl_easy_setopt(curl, CURLOPT_PASSWORD, "secret");

    /* This will list every message of the given mailbox */
    curl_easy_setopt(curl, CURLOPT_URL, "pop3://pop.example.com");

    /* Perform the list */
    res = curl_easy_perform(curl);

    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* Always cleanup */
    curl_easy_cleanup(curl);
  }

  return (int)res;
}
