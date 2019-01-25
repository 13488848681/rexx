
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

/* This is a simple example showing how to verify an e-mail address from an
 * SMTP server.
 *
 * Notes:
 *
 * 1) This example requires libcurl 7.34.0 or above.
 * 2) Not all email servers support this command and even if your email server
 *    does support it, it may respond with a 252 response code even though the
 *    address doesn't exist.
 */

int main(void)
{
  CURL *curl;
  CURLcode res;
  struct curl_slist *recipients = NULL;

  curl = curl_easy_init();
  if(curl) {
    /* This is the URL for your mailserver */
    curl_easy_setopt(curl, CURLOPT_URL, "smtp://mail.example.com");

    /* Note that the CURLOPT_MAIL_RCPT takes a list, not a char array  */
    recipients = curl_slist_append(recipients, "<recipient@example.com>");
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

    /* Perform the VRFY */
    res = curl_easy_perform(curl);

    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* Free the list of recipients */
    curl_slist_free_all(recipients);

    /* Curl won't send the QUIT command until you call cleanup, so you should
     * be able to re-use this connection for additional requests. It may not be
     * a good idea to keep the connection open for a very long time though
     * (more than a few minutes may result in the server timing out the
     * connection) and you do want to clean up in the end.
     */
    curl_easy_cleanup(curl);
  }

  return 0;
}
