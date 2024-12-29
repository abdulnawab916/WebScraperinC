/*
	A web-scraper written in C by Abdul Nawab
*/

// Includes for external libraries
#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>

// Global variable that keeps track of the number of 'chunks' 
// that have been processed by the callback function
// The variable is initialized to be '1', because we at LEAST
// will read in one chunk
int counterForChunks = 1;

// Function definitions that are needed
// (Place this into an external file if definitions get too large)
size_t getData(char *buffer, size_t itemSize, size_t nItems, void* ignoreThis);

// Entry point to project
int main(void) {
	// Initializing the library
	CURL *curl = curl_easy_init();
	// Error handling for library initialization failure
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

// Function definition for obtaining the data,
// 'size_t' is the size of the object that we are working with
size_t getData(char *buffer, size_t itemSize, size_t nItems, void* ignoreThis)
{	
	// Calculation to compute the number of bytes that we are working with
	size_t totalBytes = itemSize * nItems;
	printf("Chunk Number: %d\n Size: (%zu) bytes\n", counterForChunks, totalBytes);
	counterForChunks++;
	return totalBytes;
}


/*
TODO:
- Parse the content of the HTML page, and save it to a file of some sort
- Allow the user to input the site that they want to parse?
- This could be used by people that just want to get the text information of a site, 
- maybe I can throw it into Chat, which can then condense it, and return back a text file to 
- the user, this will be in the form of a .txt file
- Is there any way that I could make the GUI of this really nice?
- What I need to do is add some more error handling, and then create a video
- talking about my project
*/


/*
	Resources:
	'Easy Networking in C (libcurl)':
	https://www.youtube.com/watch?v=daA-KBKfJ_o
	'curl' Documentation:
	https://curl.se/libcurl/c/CURLOPT_WRITEDATA.html#:~:text=
	If%20you%20use%20the%20CURLOPT_WRITEFUNCTION,(3)%20when%20writing%20data.
	'Parsing the HTML from the text':
	https://curl.se/libcurl/c/htmltidy.html
	(The 'libcurl' library has some code within the documentation that
	can help with parsing the HTML)

*/