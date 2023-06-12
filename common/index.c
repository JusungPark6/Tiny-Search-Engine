/* Jusung Park
 * CS50 Winter 2023
 * index.c - support saving and loading index files.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libcs50/hashtable.h"
#include "../libcs50/counters.h"
#include "../libcs50/set.h"

/**************** global types ****************/
typedef struct index {
    hashtable_t* ht;
} index_t;

/**************** functions ****************/
index_t* index_new();
int index_insert(index_t* index, int docID, const char* word);
int index_get(index_t* index, int docID, const char* word);
counters_t* index_getCounter(index_t* index, char* word);
bool index_set(index_t* index, int docID, const char* word, int count);
void index_iterate(index_t* index, void* arg, void (*itemfunc)(void* arg, const char* docID, void* item));
bool indexfile_build(index_t* index, char* indexFilename);
void wordPrint(void* arg, const char* word, void* item);
void printCounter(void* arg, const int docID, const int count);
void index_delete(index_t* index);
void ht_delete(void* item);


/**************** index_new() ****************/
/* see index.h for description */
index_t* index_new()
{   
    index_t* index = malloc(sizeof(index_t));
    if (index != NULL) {
        index->ht = hashtable_new(200);         // github instructions
        if (index->ht != NULL) {
            return index;                       
        }
    } 
    return NULL;                                // return null if fails 
}

/**************** index_insert() ****************/
/* see index.h for description */
int
index_insert(index_t* index, int docID, const char* word) 
{
    if (index != NULL && word != NULL) {                            
        if (hashtable_find(index->ht, word) == NULL) {                 // if ht slot empty
            counters_t* counters = counters_new();                     // add a counter there
            counters_add(counters, docID);                             // add word to counter
            hashtable_insert(index->ht, word, counters);               // insert counter into ht
        }
        else {
            counters_add(hashtable_find(index->ht, word), docID);      // otherwise just add counter on word 
        }
    }
    return 1;
}

/**************** index_get() ****************/
/* see index.h for description */
int
index_get(index_t* index, int docID, const char* word) 
{
    if (index != NULL && word != NULL) {
        return counters_get(hashtable_find(index->ht, word), docID);   // return count
    }
    return -1;
}

counters_t*
index_getCounter(index_t* index, char* word)
{
    if (index != NULL && word != NULL) {
        return hashtable_find(index->ht, word);  
    }
    return NULL;
}

/**************** index_set() ****************/
bool
index_set(index_t* index, int docID, const char* word, int count)
{
    if (index != NULL && word != NULL) {
        if (hashtable_find(index->ht, word) == NULL) {                 // if ht slot empty
            counters_t* counters = counters_new();                     // add a counter there
            hashtable_insert(index->ht, word, counters);               // insert counter into ht
            counters_set(hashtable_find(index->ht, word), docID, count);
            return true;
        }
        else {
            counters_set(hashtable_find(index->ht, word), docID, count);
            return true;
        }
    }
    return false;
}

/**************** index_iterate() ****************/
/* see index.h for description */
void
index_iterate(index_t* index, void* arg, void (*itemfunc)(void* arg, const char* docID, void* item))
{
    if (index != NULL && itemfunc != NULL) {
        hashtable_iterate(index->ht, arg, itemfunc);    // use hashtable iterate 
    }
}

/**************** indexfile_build() ****************/
/* see index.h for description */
bool
indexfile_build(index_t* index, char* indexFilename)
{
    FILE* file;
    if ((file = fopen(indexFilename, "w")) == NULL) {
        fprintf(stderr, "Could not open/create index file for writing\n");
        exit(1);
    }
    else {
        index_iterate(index, file, wordPrint);           // iterate thru and use wordPrint
    }
    fclose(file);
    return true;
}

/**************** wordPrint() ****************/
/* see index.h for description */
void
wordPrint(void* arg, const char* word, void* item)
{
    FILE* file = arg;
    fprintf(file, "%s ", word);                            // print the word then a space
    counters_t* counters = item;                           // then
    if (counters != NULL) {
        counters_iterate(counters, arg, printCounter);     // iterate through counters and run printCounter
    }
    fprintf(file, "\n");
}

/**************** printCounter() ****************/
/* see index.h for description */
void
printCounter(void* arg, const int docID, const int count)
{
    FILE* file = arg;
    fprintf(file, "%d %d ", docID, count);                  // print out docID followed by count according to the specs
}

/**************** index_delete() ****************/
/* see index.h for description */
void
index_delete(index_t* index)
{
    hashtable_delete(index->ht, ht_delete);                 // delete the ht (which is freed)
    free(index);                                            // free the index
}

/**************** ht_delete() ****************/
/* see index.h for description */
void
ht_delete(void* item) 
{
    if (item != NULL) {
        counters_delete(item);                               // free&delete the counters stored in ht
    }
}