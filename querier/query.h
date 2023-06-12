/* Jusung Park
 * CS50 Winter 2023
 * query.h - header file for query.c
 */

#include <stdlib.h>
#include "../libcs50/counters.h"

/**************** global types ****************/
typedef struct query query_t;

/**************** functions ****************/

/**************** query_new() ****************/
/* Create a new (empty) query
 * 
 * Notes:
 *   Initializes totalIDs to 0
 * We return:
 *   pointer to a new query
 *   NULL if docIDs is NULL, or scores is NULL
 */
query_t* query_new();

/**************** query_add() ****************/
/* Adds/replaces a docID and score to the query
 * 
 * Caller Provides:
 *   Valid query
 *   int docID
 *   int Score
 * If docID already exists in counter:
 *   Sets the new docID score to the current + inputted score (accomadates or operations in querier)
 * else:
 *   Sets the counter docID and score pair to inputs
 */
void query_add(query_t* query, int docID, int score);

/**************** query_print() ****************/
/* Prints out the query
 * 
 * Caller Provides:
 *   Valid query
 * We print:
 *   Each docID,score pair in the counter
 */
void query_print(query_t* query);

/**************** query_remove() ****************/
/* Removes a certain docID from the query (by index)
 * 
 * Caller provides:
 *   Valid query
 *   Valid index int 
 * We do:
 *   Sets the docID to 0 for that index spot 
 */
void query_remove(query_t* query, int index);

/**************** query_delete() ****************/
/* Deletes the query
 * 
 * Caller Provides:
 *   Valid query
 * Caller is responsible for:
 *   later calling index_delete.
 */
void query_delete(query_t* query);

/**************** getTotalIDs() ****************/
/* Returns int TotalIds
 *
 * Caller Provides:
 *   Valid query
 * We return:
 *   int Total IDs
 */
int getTotalIDs(query_t* query);

/**************** getDocIDs() ****************/
/* Returns int* docIDs
 *
 * Caller Provides:
 *   Valid query
 * We return:
 *   int array docIDs
 */
int* getDocIDs(query_t* query);

/**************** getScores() ****************/
/* Returns counters scores
 *
 * Caller Provides:
 *   Valid query
 * We return:
 *   counters scores
 */
counters_t* getScores(query_t* query);