/*
 * Jusung Park 
 * CS50 Winter 2023
 * crawler.c program
 *
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include "../libcs50/hashtable.h"
#include "../libcs50/webpage.h"
#include "../libcs50/bag.h"
#include "../common/pagedir.h"
#include <ctype.h>
#include "../libcs50/mem.h"



/**************** functions ****************/

/**************** main ****************/
/* Calls parseArgs and crawl, and then exits zero
 */
int main(const int argc, char* argv[]);

/**************** parseArgs ****************/
/* Given arguments from the command line, extracts them into the function parameters;
 * return only if successful
 *
 * Caller provides:
 *   'argc', the number of arguments
 *   'argv', the array of arguments
 *   'seedURL', the 'internal' directory, to be used as the initial URL
 *   'pageDirectory', the (existing) directory in which to write downloaded webpages
 *   'maxDepth', an integer in range [0..10] indicating the maximum crawl depth
 * We return:
 *    if any trouble is found, print an error to stderr and exit non-zero
 * We guarantee:
 *   
 * Caller is responsible for:
 *   
 */
static void parseArgs(const int argc, char* argv[],
                      char** seedURL, char** pageDirectory, int* maxDepth);

/**************** crawl ****************/
/* Crawling from seedURL to maxDepth and saving pages in pageDirectory
 *
 * Caller provides:
 *   'seedURL', the 'internal' directory, to be used as the initial URL
 *   'pageDirectory', the (existing) directory in which to write downloaded webpages
 *   'maxDepth', an integer in range [0..10] indicating the maximum crawl depth
 * We return:
 *    if any trouble is found, print an error to stderr and exit non-zero
 * We guarantee:
 *   
 * Caller is responsible for:
 *   
 */
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth);

/**************** pageScan ****************/
/* Given a webpage, scan the given page to extract any links (URLs), ignoring non-internal URLs
 * 
 * Caller provides:
 *   'page', the given page to extract any links (URLs)
 *   'pagesSeen', the bag to be added with URLS
 *   'pages_to_crawl', the hashtable to be added with URLs
 * We return:
 *    if any trouble is found, print an error to stderr and exit non-zero
 * We guarantee:
 *   
 * Caller is responsible for:
 *   
 */
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen);