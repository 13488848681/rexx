
#include <stdio.h>
#include <curl/curl.h>

/* This is a simple example showing how to search for new messages using
 * libcurl's IMAP capabilities.
 *
 * Note that this example requires libcurl 7.30.0 or above.
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

    /* This is mailbox folder to select */
    curl_easy_setopt(curl, CURLOPT_URL, "imap://imap.example.com/INBOX");

    /* Set the SEARCH command specifing what we want to search for. Note that
     * this can contain a message sequence set and a number of search criteria
     * keywords including flags such as ANSWERED, DELETED, DRAFT, FLAGGED, NEW,
     * RECENT and SEEN. For more information about the search criteria please
     * see RFC-3501 section 6.4.4.   */
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "SEARCH NEW");

    /* Perform the custom request */
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
