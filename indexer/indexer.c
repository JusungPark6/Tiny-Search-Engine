/* Jusung Park
 * CS50 Winter 2023
 * indexer.c
 *
 * A indexer reads files from a directory by constructing file pathnames from
 * the 'pageDirectory' parameters followed by a numeric document ID. The indexer then reads
 * document files in sequential ID order, beginning at 1, until it is unable to open one of those files
 *
 * Phuc Tran, October 15th, 2021
 */

#include "../common/index.h"
#include "../libcs50/webpage.h"
#include "../libcs50/file.h"
#include <string.h>
#include "../libcs50/counters.h"
#include "../common/word.h"
#include "math.h"
#include <dirent.h>
#include <errno.h>

void indexBuild(char* pageDirectory, char* indexFilename);
void indexPage(index_t* index, webpage_t* page, int docID);
bool isCrawler(char* pageDirectory);

/**************** main() ****************/
/* see indexer.h for description */
int 
main(int argc, char *argv[])
{
    if (argc != 3) {                                            // validate argument number
        fprintf(stderr, "Incorrect number of args\n");
        exit(1);
    }

    char* pageDirectory = argv[1];                              // parse the command line
    char* indexFilename = argv[2];
    DIR* dir = opendir(argv[1]);
    if (dir) {
        closedir(dir);
    } 
    else if (ENOENT == errno) {
        fprintf(stderr, "Directory does not exist\n");
        exit(1);
    }
    else {
        fprintf(stderr, "Directory read error\n");
        exit(1);
    }
    if (!isCrawler(pageDirectory)) {                            // validate crawler directory
        fprintf(stderr, "Directory is not produced by crawler\n");
        exit(1);
    }
    indexBuild(pageDirectory, indexFilename);
}

/**************** indexBuild() ****************/
/* see indexer.h for description */
void
indexBuild(char* pageDirectory, char* indexFilename)
{
    
    char* directory = malloc((strlen(pageDirectory)) + 5);
    int docID = 1;
    FILE* file;
    int depth;
    char url[250];
    char* html; 
    webpage_t* page;
    index_t* index = index_new();

    sprintf(directory, "%s/%d", pageDirectory, docID);        // append /[docID] to filepath

    if ((file = fopen(directory, "r")) == NULL) {             // if pageDirectory/1 fails to open then exits non zero
        fprintf(stderr, "File 1 failed to read\n");
        free(directory);
        index_delete(index);
        exit(1);
    }
    fclose(file);

    while ((file = fopen(directory, "r")) != NULL) {          // run through all files in directory with docID as name
        fscanf(file, "%s\n%d", url, &depth);                  // process url, depth, and html
        html = file_readUntil(file, NULL);
        
        if ((page = webpage_new(url, depth, html)) != NULL) { // if making a new webpage succeeds
            indexPage(index, page, docID);                    // add that page info to index
        }
        docID++;
        sprintf(directory, "%s/%d", pageDirectory, docID);    // get next filepath ready
        free(html);
        free(page);
        fclose(file);
    }
    free(directory);
    indexfile_build(index, indexFilename);
    index_delete(index);
}

/**************** indexPage() ****************/
/* see indexer.h for description */
void
indexPage(index_t* index, webpage_t* page, int docID)
{
    int pos = 0;
    char* word;
    while((word = webpage_getNextWord(page, &pos)) != NULL) {     // interate through words
        if (strlen(word) < 3) {                                   // ignore trivial words
            free(word);
            continue;
        }
        word = normalizeWord(word);                               // make word lowercase
        index_insert(index, docID, word);                         // insert into index 
        free(word);
    }
}

/**************** isCrawler() ****************/
/* see indexer.h for description */
bool
isCrawler(char* pageDirectory)
{
    char* directory = malloc((strlen(pageDirectory)) + 10);  
    sprintf(directory, "%s/.crawler", pageDirectory);       // add /.crawler to filepath
    FILE *file; 
    if ((file = fopen(directory, "r")))                     // check if crawler file exists in directory
    {
        fclose(file);
        free(directory);
        return true;
    }
    free(directory);
    return false;
}