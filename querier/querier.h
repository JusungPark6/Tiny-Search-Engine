/* Jusung Park
 * CS50 Winter 2023
 * querier.h - header file for CS50 querier.c
 *
 */

#include "../libcs50/hashtable.h"
#include "../common/word.h"
#include "../common/index.h"
#include "query.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]);
bool checkArgs(char* pageDirectory, char* indexFilename);
query_t* runQuery(int argc, char* argv[], char* input);
char** tokenize(char* input);
query_t* queryOperation(query_t* query1, query_t* query2, char* operator);
void outputQuery(query_t* query, char* pareDirectory);
bool verifyInput(char* input);
query_t* makeQuery(char* word, index_t* index);
void iterateFunc(void* arg, const int docID, const int count);
index_t* loadIndex(char* filePath);


/**************** functions ****************/

/**************** main() ****************/
/* Reads lines from stdin and initializes other modules
 *
 * Caller provides:
 *  Pathname of a directory produced by crawler
 *  Pathname for an indexFile to be read
 * 
 */
int main(int argc, char *argv[]);

/**************** checkArgs() ****************/
/* Checks main() caller provided args 
 *
 * Exits non-zero if:
 *   indexFilename is not a path that leads to an openable index file
 *   pageDirectory./crawler is not openable
 *   pageDirectory/1 is not openable 
 */
bool checkArgs(char* pageDirectory, char* indexFilename);

/**************** runQuery() ****************/
/* Runs the query and deals with the and/or operators 
 * 
 * Prints an error if:
 *   String separation fails 
 *   input does not contain just spaces and chars 
 * Notes:
 *   Takes input and turns it into a 2d char array
 * Returns: 
 *   Combined query after all and/or operators 
 * 
 */
query_t* runQuery(int argc, char* argv[], char* input);

/**************** tokenize() ****************/
/* Builds an array of words using isspace to separate words by spaces
 *  
 * Ignores: 
 *   Spaces that start or end the input
 *   Multiple spaces between words
 * 
 * Exits: 
 *   Non-zero if "or" or "and" start or end the input sequence
 *   Non-zero if "or" and/or "and" are next to one another in the input sequence
 */
char** tokenize(char* input);

/**************** queryOperation() ****************/
/* Runs an "and" or "or" operation between two queries
 *
 * Inputs:
 *   2 queries and an "or" or "and" operator
 * Prints error if:
 *   Incorrect operator provided
 * Notes:
 *   Returns a new query and deletes both inputs
 *   If an empty query is provided, it returns a copy of the other query
 * 
 */
query_t* queryOperation(query_t* query1, query_t* query2, char* operator);

/**************** outputQuery() ****************/
/* Removes IDs one by one based on which hash the largest score and prints them out with score, docID, and URL
 *
 * Prints Error if:
 *   Query does not match and docIDs
 * Exits non-zero if:
 *   File fails to open
 * 
 */
void outputQuery(query_t* query, char* pareDirectory);

/**************** verifyInput() ****************/
/* Verifies char* input is a string of just uppercase and lowercase letters with space charaters
 *
 * Returns:
 *   False if contains a non-letter/space character
 *   Else returns true
 */
bool verifyInput(char* input);

/**************** makeQuery() ****************/
/* Creates a query from a single word and index
 *
 * Caller provides:
 *   Valid index
 * We return:
 *   A new query with docIDs of the word based off the index 
 */
query_t* makeQuery(char* word, index_t* index);

/**************** iterateFunc() ****************/
/* Function used to iterate through the index
 *
 * Notes:
 *   Runs query_add on the newQuery in makeQuery
 * 
 */
void iterateFunc(void* arg, const int docID, const int count);

/**************** loadIndex() ****************/
/* Function used to load and .index file into an index internal structure
 *
 * Notes:
 *   uses an "iterator" to keep track of which word is being processed from the index file 
 * Returns: 
 *   index
 * Exits non-zero if:
 *   File cannot open
 */
index_t* loadIndex(char* filePath);