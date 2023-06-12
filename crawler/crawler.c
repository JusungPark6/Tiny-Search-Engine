/*
 * Jusung Park 
 * CS50 Winter 2023
 * crawler.c program
 *
 *
 */


#include "crawler.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../libcs50/hashtable.h"
#include "../libcs50/webpage.h"
#include "../libcs50/bag.h"
#include "../libcs50/mem.h"
#include "../common/pagedir.h"
#include <ctype.h>


/*********** function declarations ******/
static void parseArgs(const int argc, char* argv[],
                      char** seedURL, char** pageDirectory, int* maxDepth);
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth);
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen);

/***************** main *****************/
int main(const int argc,  char* argv[]){
    char* seedURL;
    char* pageDirectory;
    int maxDepth;
    parseArgs(argc, argv, &seedURL, &pageDirectory, &maxDepth);
    crawl(seedURL, pageDirectory, maxDepth);
}

/************ parseArgs function ************/
void parseArgs(const int argc, char* argv[], char** seedURLp, char** pageDirectoryp, int* maxDepthp){
    const char* progName = argv[0]; //name of program

    if (argc !=4) {
        fprintf(stderr, "usage: %s seedURL pageDirectory maxDepth\n", progName);
        exit(1);
    }
    *seedURLp = argv[1];
    *pageDirectoryp = argv[2];

    // normalized seedURL and validate that it is an internal URL
	char* normalizedURL = normalizeURL(argv[1]);
	if (normalizedURL == NULL || !isInternalURL(normalizedURL)){
		fprintf(stderr, "seedURL is invalid or not internal. Please recall with an url begins with the correct internal prefix\n");
		exit(1);
	}
	*seedURLp = normalizedURL;
    
    // Call pagedir_init()
	if (!pagedir_init(argv[2])){
		fprintf(stderr, "the existing directory could not be opened to write\n");	
		exit(1);
	}
	*pageDirectoryp = argv[2];

    // check if maxDepth is a digit
    int lengthMaxDepth = strlen(argv[3]);
	for (int i = 0; i < lengthMaxDepth; i++) {
		if (!isdigit(argv[3][i])) {
			fprintf (stderr, "maxDepth is not an invalid (not an integer)\n");
		    exit(1);
		}
    } 
    //check if maxDepth is null or out of range
    if (argv[3] == NULL || atoi(argv[3]) > 10 || atoi(argv[3]) < 0){
		fprintf(stderr, "maxDepth is invalid or out of range. Please recall with maxDepth range [0,10]\n");
		exit(1);
	}
	*maxDepthp = atoi(argv[3]);
}

/************** crawler function***************/
static void crawl (char* seedURL, char* pageDirectory, int maxDepth){
    //create hashtable
    int numSlots = 200;
	hashtable_t* URLtable = hashtable_new(numSlots);
	if (URLtable != NULL){
		hashtable_insert(URLtable, seedURL, "");
	} else{
	  fprintf(stderr, "Hashtable not created\n");
    exit(1);	
	}


    // initialize the bag and add a webpage representing the seedURL at depth 0
	bag_t* URLs = bag_new();
	webpage_t* page = webpage_new(seedURL, 0, NULL);
	if (URLs != NULL && page != NULL){
		bag_insert(URLs, page);
	} else{
		if (URLs == NULL){
    	fprintf(stderr, "Bag not created \n");
    	exit(1);			
		}
		else if (page == NULL) {
    	fprintf(stderr, "Webpage not created\n");
    	exit(1);
  	}
    }
    int docID = 1;

	// pulling the initial webpage from the bag
	webpage_t* front_page = bag_extract(URLs); 
	while (front_page != NULL){

		// 	fetch the HTML for that webpage
		if (webpage_fetch(front_page)){
			printf("%d Fetched: %s\n", webpage_getDepth(front_page), webpage_getURL(front_page));
			pagedir_save(front_page, pageDirectory, docID);
			docID = docID + 1;

			// checking if docID is within maxDepth
			if (webpage_getDepth(front_page) < maxDepth){
				printf("%d Scanning: %s\n", webpage_getDepth(front_page), webpage_getURL(front_page));
				pageScan(front_page, URLs, URLtable);
			}
		}
    // Fetch next webpage
    webpage_t* nextPage = bag_extract(URLs);

    // Delete the current webpage
    webpage_delete(front_page);

    // Set currentPage as next
    front_page = nextPage;
	}

	// delete hashtable and bag
	hashtable_delete(URLtable, NULL);
	bag_delete(URLs, NULL);
}

/**************** pageScan ****************/
/* see crawler.h for description */
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen){

	// Checking if bag or hashtable is null
	if (pagesToCrawl == NULL){
    fprintf(stderr, "Invalid Bag.\n");  
    return;
  }

  if (pagesSeen == NULL){
    fprintf(stderr, "Error, Invalid Hashtable.\n");  
    return;
  }

	int pos = 0;
	char* result;
	int currentDepth = webpage_getDepth(page);

	// Checking for another webpage in this depth
	while ((result = webpage_getNextURL(page, &pos)) != NULL) {
    printf("%d Found url: %s\n", currentDepth + 1, result);

		// Checking for internal URL and insert that into a hashtable
		if (isInternalURL(result)){

			printf("%s\n", result);

			if (hashtable_insert(pagesSeen, result, "")){

				// Create webpage_t for URL and insert the webpage into the bag
				webpage_t* temp = webpage_new(result, currentDepth + 1, NULL);
				if (temp != NULL){
					bag_insert(pagesToCrawl, temp);
					printf("%d Added: %s\n", currentDepth + 1, result);
				}
			} else{
					printf("%d IgnDupl: %s\n", currentDepth + 1, result);
					mem_free(result);
				}		
		} else{
				printf("%d IgnExtrn: %s\n", currentDepth + 1, result);
				mem_free(result);		
		}
	}
	mem_free(result);
}