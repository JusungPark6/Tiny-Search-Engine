/* Jusung Park
 * CS50 Winter 2023
 * query.c - A module CS50 Palmer
 *
 */

#include "../libcs50/counters.h"
#include <stdlib.h>

/**************** global types ****************/
typedef struct query {
    int* docIDs;
    counters_t* scores;
    int totalIDs;
} query_t;

/**************** functions ****************/
query_t* query_new();
void query_add(query_t* query, int docID, int score);
void query_print(query_t* query);
void query_remove(query_t* query, int index);
void query_delete(query_t* query);
int getTotalIDs(query_t* query);
int* getDocIDs(query_t* query);
counters_t* getScores(query_t* query);

/**************** query_new() ****************/
/* see query.h for description */
query_t*
query_new()
{
    query_t* query = malloc(sizeof(query_t));
    if (query != NULL) {
        query->docIDs = calloc(200, sizeof(int));
        query->scores = counters_new();
    }
    if (query->docIDs != NULL) {
        if (query->scores != NULL) {
            query->totalIDs = 0;
            return query;
        }
    }
    return NULL;
}

/**************** query_add() ****************/
/* see query.h for description */
void
query_add(query_t* query, int docID, int score)
{
    if (query != NULL) {
        query->docIDs[query->totalIDs] = docID;
        if (counters_get(query->scores, docID) == 0) {
            counters_set(query->scores, docID, score);
            query->totalIDs++;
        }
        else {
            counters_set(query->scores, docID, counters_get(query->scores, docID) + score);
        }
    }
}

/**************** query_print() ****************/
/* see query.h for description */
void
query_print(query_t* query)
{
    if (query != NULL) {
        for(int i = 0; i < query->totalIDs; i++) {
            printf("docID: %d, count: %d\n", query->docIDs[i], counters_get(query->scores, query->docIDs[i]));
        }
    }
}

/**************** query_remove() ****************/
/* see query.h for description */
void
query_remove(query_t* query, int index)
{
    if (query != NULL) {
        if (index < query->totalIDs) {
            query->docIDs[index] = 0;
        }
    }
}

/**************** query_delete() ****************/
/* see query.h for description */
void
query_delete(query_t* query) 
{
    if (query != NULL) {
        free(query->docIDs);
        counters_delete(query->scores);
        free(query);
    }
}

/**************** getTotalIDs() ****************/
/* see query.h for description */
int
getTotalIDs(query_t* query)
{
    return query->totalIDs;
}

/**************** getDocIDs() ****************/
/* see query.h for description */
int*
getDocIDs(query_t* query)
{
    return query->docIDs;
}

/**************** getScores() ****************/
/* see query.h for description */
counters_t*
getScores(query_t* query)
{
    return query->scores;
}