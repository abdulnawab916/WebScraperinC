/*
	A web-scraper written in C by Abdul Nawab
*/

#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>

// Callback function header, we have to follow the prototype below
// of the parameters

// I initialize the number of Chunks to be 1, and this will be incremented each 
// time that the callback function is invoked
// I could not define this locally because it would just reset the variable to be '1'
// on each invokation from the function
int counterForChunks = 1;

size_t getData(char *buffer, size_t itemSize, size_t nItems, void* ignoreThis);

// Entry point
int main(void) {
	CURL *curl = curl_easy_init();
	if (!curl){
		// Print to error stream
		fprintf(stderr, "Initialization failed\n");
}
	// Generates initial response from trying to acquire data from the following URL
	curl_easy_setopt(curl, CURLOPT_URL, "https://abdulnawab916.github.io/PersonalWebsite/");
	
	// The callback is invoked however many times that it is needed
	// There can be a maximum limit on it, but that is not needed in our case
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, getData);
	CURLcode responseCode = curl_easy_perform(curl);

	// Basic error handling
	if (responseCode != CURLE_OK){
		fprintf(stderr, "Damn bruh, it ain't work!: %s\n", curl_easy_strerror(responseCode));
	}
	curl_easy_cleanup(curl);
}

size_t getData(char *buffer, size_t itemSize, size_t nItems, void* ignoreThis){
	
	// Calculation to compute the number of bytes that we are working with
	size_t totalBytes = itemSize * nItems;
	printf("Chunk Number: %d\n Size: (%zu) bytes\n", counterForChunks, totalBytes);
	counterForChunks++;
	return totalBytes;
	// Iterate through the buffer and print out the contents of the current chunk 

}

/*
Resources:
'Easy Networking in C (libcurl)':
https://www.youtube.com/watch?v=daA-KBKfJ_o
'curl' Documentation:
https://curl.se/libcurl/c/CURLOPT_WRITEDATA.html#:~:text=
If%20you%20use%20the%20CURLOPT_WRITEFUNCTION,(3)%20when%20writing%20data.
*/