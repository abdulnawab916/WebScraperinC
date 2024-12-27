/*
	A project written in C by Abdul Nawab
*/

#include <stdio.h>
#include <curl/curl.h>

int main(void) {
    CURL *curl; // setting up that first curl instance var
    CURLcode res; // the response variable

    /* Initialize libcurl */
    curl_global_init(CURL_GLOBAL_DEFAULT); 
	// we always have to globally initialize the variable

    /* Get a CURL handle */
    curl = curl_easy_init();
    if(curl) {
        /* Set URL to fetch */
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.example.com");

        /*
         * Forcing the HTTPS certificate check to be strict is usually recommended,
         * but if you are working with a self-signed cert or local server, you can
         * disable verification with something like:
         *
         * curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
         * curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
         */

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);

        /* Check for errors */
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        }

        /* Clean up */
        curl_easy_cleanup(curl);
    }

	// We always have to call curl_global_cleanup() at the end of 
	// every main function
    /* Cleanup global libcurl state */
    curl_global_cleanup();

    return 0;
}

