/* Jusung Park
 * CS50 Winter 2023
 * indexer.h - header file for CS50 indexer module
 */

#include "../common/index.h"
#include <../libcs50/webpage.h>
#include "../libcs50/file.h"
#include "../libcs50/counters.h"
#include "../common/word.h"
#include <string.h>
#include "math.h"

void indexBuild(char* pageDirectory, char* indexFilename);
void indexPage(index_t* index, webpage_t* page, int docID);
bool isCrawler(char* pageDirectory);

/**************** functions ****************/

/**************** main() ****************/
/* Parses arguments and initializes other modules
 *
 * Caller provides:
 *  Pathname of a directory produced by crawler
 *  Pathname for an indexFile that will be produced or overwritten
 * We exit nonzero:
 *  If directory is not produced by crawler 
 *  If too many or too little arguments are provided 
 */
int main(int argc, char *argv[]);

/**************** indexBuild() ****************/
/* Builds an in-memory index from webpage files it finds in the pageDirectory
 *
 * Caller provides:
 *   Valid pathname to crawler directory
 *   Valid pathname for indexFile
 * We guarantee:
 *   indexFile will be overwritten or produced
 */
void indexBuild(char* pageDirectory, char* indexFilename);

/**************** indexPage() ****************/
/* Scans a webpage document to add its words to the index
 *
 * Caller provides:
 *   Valid index
 *   Valid webpage
 *   Valid docID
 * Notes:
 *   Continuously loops through words on the page and adds them to the
 *   index/iterates the counters to keep track. 
 */
void indexPage(index_t* index, webpage_t* page, int docID);

/**************** isCrawler() ****************/
/* Checks if directory is a crawler produced directory
 *
 * Caller provides:
 *   Valid directory path
 * We return:
 *   false if dir does not contain ./crawler
 *   true if dir does contain ./crawler
 */
bool isCrawler(char* pageDirectory);