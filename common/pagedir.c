/* Jusung Park
 * CS50 Winter 2023
 * pagedir module for crawler module
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../libcs50/mem.h"
#include "../libcs50/webpage.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/bag.h"
#include "pagedir.h"


/**************** functions ****************/

/**************** pagedir_init ****************/
/* see pagedir.h for description */
bool pagedir_init(const char* pageDirectory){
  
  // construct the pathname for the .crawler file in that directory
  // length of pageDirectory and length of "./crawler"
  char* pathname = mem_malloc(strlen(pageDirectory) + 10);
  sprintf(pathname, "%s/.crawler", pageDirectory);

  // open the file for writing; on error, return false.
  // close the file and return true.
  FILE* fileOpener = fopen(pathname, "w");
  if(fileOpener == NULL){
    mem_free(pathname);
    return false;
  } else{
    mem_free(pathname);
    fclose(fileOpener);
    return true;
  }

}

/**************** pagedir_save ****************/
/* see pagedir.h for description */
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID){

  // construct the pathname for the page file in pageDirectory (pathDirectory/ID)
  char* pagedirectoryID = mem_malloc(strlen(pageDirectory) + 5);
  sprintf(pagedirectoryID, "%s/%d", pageDirectory, docID);

  // open the file for writing
  FILE* fileOpener = fopen(pagedirectoryID, "w");
  if(fileOpener != NULL){

    // print the URL, depth, and contents of the webpage
    char* url = webpage_getURL(page);
    fprintf(fileOpener, "%s\n", url);

    int depth = webpage_getDepth(page);
    fprintf(fileOpener, "%d\n", depth);

    char* html = webpage_getHTML(page);
    fprintf(fileOpener, "%s\n", html);

    mem_free(pagedirectoryID);
    fclose(fileOpener);
  } else{
    fprintf(stderr, "pagedir_save was not able to open or write a file in the pageDirectory folder\n");
    mem_free(pagedirectoryID);
  }

}

/**************** pagedir_validate ****************/
/* Verify whether dir is a Crawler-produced directory
 *
 * Caller provides:
 *   'pageDirectory', the directory to check for Crawler-produced
 * 
 * We return:
 *    true if the directory is a Crawler-produced directory; false if otherwise
 *    if any trouble is found, print an error to stderr and exit non-zero
 * 
 * We guarantee:
 *   
 * Caller is responsible for:
 *   
 */
bool pagedir_validate(char* pageDirectory){
  // construct the pathname for the .crawler file in that directory
  // length of pageDirectory and length of "./crawler"
  char* pathname = mem_malloc(strlen(pageDirectory) + 10);
  sprintf(pathname, "%s/.crawler", pageDirectory);

  // open the file for writing; on error, return false.
  // close the file and return true.
  FILE* fileReader = fopen(pathname, "r");
  if(fileReader == NULL){
    mem_free(pathname);
    return false;
  } else{
    mem_free(pathname);
    fclose(fileReader);
    return true;
  }  
}