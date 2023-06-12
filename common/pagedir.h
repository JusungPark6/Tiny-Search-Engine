/* Jusung Park
 * 
 * 
 */


#include <stdio.h>
#include <stdbool.h>
#include "../libcs50/webpage.h"

/**************** functions ****************/

/**************** pagedir_init ****************/
/* Opens a file for writing 
 *
 * Caller provides:
 *   'pageDirectory', the directory folder name
 * We return:
 *    if any trouble is found, print an error to stderr and exit non-zero
 * We guarantee:
 *   
 * Caller is responsible for:
 *   
 */
bool pagedir_init(const char* pageDirectory);

/**************** pagedir_save ****************/
/* Opens the file and print out the page's URL, depth, contents, and file
 *
 * Caller provides:
 *   'page', the URL to print content
 *   'pageDirectory', the directory folder to print out
 *   'docID', the ID of the URL link
 * We return:
 *    if any trouble is found, print an error to stderr and exit non-zero
 * We guarantee:
 *   
 * Caller is responsible for:
 *   
 */
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);

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
bool pagedir_validate(char* pageDirectory);


/**************** pagedir_validate ****************/
/* Load a page from a file in that directory
 *
 * Caller provides:
 *   'pageDirectoryID', the file from a Crawler-produced directory to search and load a page
 * 
 * We return:
 *    true if the directory is a Crawler-produced directory; false if otherwise
 *    if any trouble is found, print an error to stderr and exit non-zero
 * 
 * We guarantee:
 *    The file is from a Crawler-produced directory
 *   
 * Caller is responsible for:
 *   
 */
void pagedir_load(char* pageDirectoryID);