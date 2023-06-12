/* Jusung Park
 * CS50 Winter 2023
 * index.h - header file for index.c in supporting saving and loading index files.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libcs50/hashtable.h"
#include "../libcs50/set.h"
#include "../libcs50/counters.h"

/**************** global types ****************/
typedef struct index index_t;

/**************** functions ****************/

/**************** index_new ****************/
/* Create a new (empty) index.
 * 
 * We return:
 *   pointer to a new set, or NULL if error.
 * Caller is responsible for:
 *   later calling index_delete.
 */
index_t* index_new();

/**************** index_insert ****************/
/* Increment/create counter, identified by word (string), into the given index.
 *
 * Caller provides:
 *   Valid pointer to index, valid string for word, valid int for docID
 * We return:
 *   Value of counter
 * Notes:
 *   The key string is copied for use by the hashtable; that is, the module
 *   is responsible for allocating memory for a copy of the key string, and
 *   later deallocating that memory; thus, the caller is free to re-use or 
 *   deallocate its key string after this call.  
 */
int index_insert(index_t* index, int docID, const char* word);

/**************** index_get() ****************/
/* Return the item associated with the given key.
 *
 * Caller provides:
 *   Valid pointer to index, valid string for word, valid int for docID
 * We return:
 *   Value of counter, -1 if fail
 * 
 */
int index_get(index_t* index, int docID, const char* word);

/**************** index_getCounter() ****************/
/* Returns the counter associated with the given word
 *
 * Caller provides:
 *   Valid pointer to index, valid string for word
 * We return: 
 *   A counter
 * 
 */
counters_t* index_getCounter(index_t* index, char* word);

/**************** index_set() ****************/
/* Sets the specific counter to a specific count
 *
 * Caller provides:
 *   Valid pointer to index, valid string for word, valid int for docID, valid int for count
 * We return:
 *   True if success
 *   false if fail
 * Notes:
 *   Will create a new counter if index slot is empty
 * 
 */
bool index_set(index_t* index, int docID, const char* word, int count);

/**************** index_iterate ****************/
/* Iterate over all items in the table; in undefined order.
 *
 * Caller provides:
 *   valid pointer to int, 
 *   arbitrary void*arg pointer,
 *   itemfunc that can handle a single (docID, item) pair.
 * We do:
 *   nothing, if ht==NULL or itemfunc==NULL.
 *   otherwise, call the itemfunc once for each item, with (arg, docID, item).
 */
void index_iterate(index_t* index, void* arg, void (*itemfunc)(void* arg, const char* docID, void* item));

/**************** indexfile_build ****************/
/* Builds the index file from an index
 *
 * Caller provides:
 *   valid index
 *   valid filepath for .index file 
 * We do:
 *   print index information into file according to specified format:
 *       [word] [docID] [count] [docID] [count] ... \n
 *       [nextWord] ... 
 */

bool indexfile_build(index_t* index, char* indexFilename);

/**************** wordPrint ****************/
/* Prints the words onto the index file
 *
 */
void wordPrint(void* arg, const char* word, void* item);

/**************** printCounter ****************/
/* Prints the docID and count onto the index file
 *
 */
void printCounter(void* arg, const int docID, const int count);

/**************** index_delete() ****************/
/* Delete index
 *
 * Caller provides:
 *   valid Index
 * We do:
 *   if index==NULL, do nothing.
 *   otherwise, call hashtable_delete and use deletefunc ht_delete
 * 
 */
void index_delete(index_t* index);

/**************** ht_delete() ****************/
/* Delete function for hashtable
 *
 * Caller provides:
 *   valid item (counter)
 * We do:
 *   if item==NULL, do nothing.
 *   otherwise, call counter_delete(); 
 * 
 */
void ht_delete(void* item);