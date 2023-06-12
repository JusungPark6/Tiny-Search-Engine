/* Jusung Park
 * CS50 Winter 2023
 * querier.c - querier file for the querier module
 *
 */

#include "../libcs50/hashtable.h"
#include "../common/word.h"
#include "../common/index.h"
#include "../libcs50/file.h"
#include "query.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* Function declarations */
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


/**************** Functions ****************/

/**************** main() ****************/
/* see querier.h for description */
int
main(int argc, char* argv[])
{
    if (checkArgs(argv[1], argv[2])) {
        char* input;
        query_t* query;
        while ((input = file_readLine(stdin)) != NULL) {
            query = runQuery(argc, argv, input);
            if (query != NULL) {
                outputQuery(query, argv[1]);
            }
            free(input);
            query_delete(query);
        }
    }
    return 0;
}

/**************** checkArgs() ****************/
/* see querier.h for description */
bool
checkArgs(char* pageDirectory, char* indexFilename)
{
    FILE* file; 
    if ((file = fopen(indexFilename, "r")) != NULL) {                   // test if indexFile is openable 
        fclose(file);
        char* directory = malloc((strlen(pageDirectory)) + 10);  
        sprintf(directory, "%s/.crawler", pageDirectory);               // test if pageDirectory./crawler is openable
        if ((file = fopen(directory, "r")) != NULL)           
        {
            fclose(file);
            sprintf(directory, "%s/1", pageDirectory);
            if ((file = fopen(directory, "r")) != NULL) {               // test if pageDirectory/1 is openable
                fclose(file);
                free(directory);
                return true;
            }
            free(directory);
            fprintf(stderr, "Error: pageDirectory/1 cannot be read\n");
            exit(1);
        }
        free(directory);
        fprintf(stderr, "Error: pageDirectory/.crawler cannot be read\n");
        exit(1);
        return false;
    }   
    else {
        fprintf(stderr, "Error: Index file cannot be read\n");
        exit(1);
        return false;
    }

}


/**************** runQuery() ****************/
/* see querier.h for description */
query_t*
runQuery(int argc, char* argv[], char* input) 
{
    char** wordList;    
    query_t* queryInternal = query_new();                                                                        // create new external and internal queries 
    query_t* queryExternal = query_new();
    if (verifyInput(input)) {                                                                                    // verify input is a space or char
        if ((wordList = tokenize(input)) != NULL) {                                                              // tokenize function and create an array of words
            int i = 0;
            printf("Current query: [ ");
            while (strcmp(wordList[i], "") != 0) {                                                               // print out current query
                printf("%s ", wordList[i]);
                i++;
            }
            printf("]\n"); 
            i = 0;
            index_t* index = loadIndex(argv[2]);
            while (strcmp(wordList[i], "") != 0) {                                                               // for each word
                if (strcmp(wordList[i], "or") == 0) {                                                            // if or then or operation the internal and external 
                    queryExternal = queryOperation(queryInternal, queryExternal, "or"); 
                    queryInternal = query_new();                                                                 // reset the internal
                }
                else {
                    queryInternal = queryOperation(queryInternal, makeQuery(wordList[i], index), "and");         // otherwise and the internal with the word
                }
                i++;
            }
            index_delete(index);
            queryExternal = queryOperation(queryInternal, queryExternal, "or");                                  // if reach the end of query, or the internal and external 
        }
        else {                                                                                             
            query_delete(queryInternal);
            fprintf(stderr, "Error: String separation into words failed\nNext query: \n");
        }
        for (int i = 0; i < 100; i++) {                                                                          // free the 2d char array
            free(wordList[i]);
        }
        free(wordList);
    }
    else {
        query_delete(queryInternal);
        fprintf(stderr, "Error: Input must contain only letters and spaces\nNext query: \n");
        return NULL;
    }
    return queryExternal;
}


/**************** tokenize() ****************/
/* see querier.h for description */
char**
tokenize(char* input)
{
    char buffer[100];
    memset(buffer, 0, sizeof(buffer));
    int bufferIndex = 0;
    bool space;
    int lastOperator;
    char** wordList = (char**)calloc(100, sizeof(char*));                                  // malloc out first row
    int wordIndex = 0;
    for (int i = 0; i < 100; i++) {
        wordList[i] = (char*)calloc(100, sizeof(char));                                    // malloc out a string for each column in array
    }
    for (int i = 0; i < strlen(input); i++) {  
        if ((isspace(input[i]) != 0) && bufferIndex == 0) {                                // ignore starting spaces
            continue;
        }
        if (isspace(input[i]) != 0) {                                                      // use isspace to separate words
            if (strcmp(buffer, "and") == 0) {                                              // check if buffer word is and
                bufferIndex = 0;                                                           // if so remove it and dont ad to wordIndex
                memset(buffer, 0, sizeof(buffer));                                         // reset buffer 
                if (wordIndex == lastOperator+1) {                                         // check if current index is 1 past lastOperator
                    fprintf(stderr, "Error: Adjacent operators\n");
                    exit(1);
                }
                lastOperator = wordIndex-1;                                                // since and is removed wordIndex-1 and lastOperator+1 is necessary 
                continue;
            }        
            if (strcmp(buffer, "or") == 0) {                                               // check if string is or
                if (wordIndex == lastOperator+1) {                                           // check for adjacent operators 
                    fprintf(stderr, "Error: Adjacent operators\n");
                    exit(1);
                }                               
                lastOperator = wordIndex;                                                  // mark position of last operator 
            }  
            if (!space) {                                                                  // enable multiple spaces between words
                strcpy(wordList[wordIndex], buffer);                                       // copy over the buffer if space is found
                wordIndex++;
                bufferIndex = 0;
                memset(buffer, 0, sizeof(buffer));   
            }                
            space = true;                     
        }
        else {
            space = false;
            buffer[bufferIndex] = tolower(input[i]);
            bufferIndex++;     
        }
    }

    if (buffer[0] != 32) {                                                                // check if buffer is a space (since empty spaces trigger word being added will miss last word)
        strcpy(wordList[wordIndex], buffer);                                              // add in the word at the end of the input
    }

    if (strcmp(wordList[0], "or") == 0 || strcmp(wordList[0], "and") == 0) {
        fprintf(stderr, "Error: Operator cannot start input sequence\n");
        exit(1);
    }                                                                                     // errors for staring input or ending input with operator
    if (strcmp(wordList[wordIndex], "or") == 0 || strcmp(wordList[wordIndex], "and") == 0) {
        fprintf(stderr, "Error: Operator cannot end input sequence\n");
        exit(1);
    }
    return wordList;
}

/**************** queryOperation() ****************/
/* see querier.h for description */
query_t*
queryOperation(query_t* query1, query_t* query2, char* operator) 
{
    query_t* queryNew = query_new();
    if (getTotalIDs(query1) == 0) {                                                                                          // if query1 empty just return other query
        for (int i = 0; i < getTotalIDs(query2); i++) {
            query_add(queryNew, getDocIDs(query2)[i], counters_get(getScores(query2), getDocIDs(query2)[i]));   
        }
        query_delete(query1);
        query_delete(query2);
        return queryNew;
    }
    if (getTotalIDs(query2) == 0) {                                                                                          // if query2 empty just return other query
        for (int i = 0; i < getTotalIDs(query1); i++) {
            query_add(queryNew, getDocIDs(query1)[i], counters_get(getScores(query1), getDocIDs(query1)[i]));   
        }
        query_delete(query1);
        query_delete(query2);
        return queryNew;
    }

    if (strcmp(operator, "and") == 0) {                                                                                      // if operator is and
        for (int i = 0; i < getTotalIDs(query1); i++) { 
            for (int j = 0; j < getTotalIDs(query2); j++) {                                                                  // for each DocID in each query
                if (getDocIDs(query1)[i] == getDocIDs(query2)[j]) {                                                          // compare and if same
                    if (counters_get(getScores(query1), getDocIDs(query1)[i]) >  
                    counters_get(getScores(query2), getDocIDs(query2)[j])) {                  
                        query_add(queryNew, getDocIDs(query2)[j], counters_get(getScores(query2), getDocIDs(query2)[j]));    // add the lower docID score to queryNew
                    }
                    else {
                        query_add(queryNew, getDocIDs(query1)[i], counters_get(getScores(query1), getDocIDs(query1)[i]));   
                    }
                }
            }
        }
        query_delete(query1);
        query_delete(query2);
        return queryNew;
    }

    else if (strcmp(operator, "or") == 0) {                                                                                  // if operator is or
        for (int i = 0; i < getTotalIDs(query1); i++) {                                                                      // add each docID in first query
            query_add(queryNew, getDocIDs(query1)[i], counters_get(getScores(query1), getDocIDs(query1)[i]));
        }
        for (int i = 0; i < getTotalIDs(query2); i++) {                                                                      // add each docID in second query, query_add takes care of adding scores together
            query_add(queryNew, getDocIDs(query2)[i], counters_get(getScores(query2), getDocIDs(query2)[i]));
        }
        query_delete(query1);
        query_delete(query2);
        return queryNew;
    }
    else {
        fprintf(stderr, "Error: Incorrect operator provided to queryOperaton\n");
        query_delete(query1);
        query_delete(query2);
        exit(1);
    }
}

/**************** outputQuery() ****************/
/* see querier.h for description */
void
outputQuery(query_t* query, char* pageDirectory)
{
    if (getTotalIDs(query) == 0) {         
        fprintf(stderr, "No Documents Match. \n"); 
    }
    else {
        FILE* file;
        char URL[250];
        char dir[250];
        int idCount = getTotalIDs(query);
        while (idCount != 0) {                                                                    // one by one remove IDs until none are left
            int highestCount = 0;
            int index = 0;  
            for(int i = 0; i < getTotalIDs(query); i++) {                                         // iterate through to find highestCount and remove
                if (counters_get(getScores(query), getDocIDs(query)[i]) > highestCount) {
                    highestCount = counters_get(getScores(query), getDocIDs(query)[i]);
                    index = i;
                }
            }
            sprintf(dir, "%s/%d", pageDirectory, index+1);                                        // scan crawler files for URL
            if ((file = fopen(dir, "r")) != NULL) {
                fscanf(file, "%s", URL);
                printf("Score: %d || docID: %d || URL: %s \n", counters_get(getScores(query), getDocIDs(query)[index]), getDocIDs(query)[index], URL); 
                counters_set(getScores(query), getDocIDs(query)[index], 0);                       // set the count for that ID to 0 (so will not repeat itself)
                idCount--;  
                fclose(file); 
            }
            else {
                fprintf(stderr, "Error: File failed to open\n");
                exit(1);
            }
        }
    }
}

/**************** verifyInput() ****************/
/* see querier.h for description */
bool
verifyInput(char* input)
{
    for (int i = 0; i < strlen(input); i++) {          
        if (input[i] >= 97 && input[i] <= 122) {           // check if lowercase
            continue;
        } 
        else if (input[i] >= 65 && input[i] <= 90) {       // check if uppercase
            continue;
        }
        else if (isspace(input[i]) != 0) {                 // check if space char 
            continue;
        }
        else {
            return false;
        }

    }
    return true;
}

/**************** makeQuery() ****************/
/* see querier.h for description */
query_t*
makeQuery(char* word, index_t* index)
{
    query_t* queryNew = query_new();
    counters_iterate(index_getCounter(index, word), queryNew, iterateFunc);
    return queryNew;
}

/**************** iterateFunc() ****************/
/* see querier.h for description */
void
iterateFunc(void* arg, const int docID, const int count) 
{
    query_add(arg, docID, count);
}

/**************** loadIndex() ****************/
/* see querier.h for description */
index_t*
loadIndex(char* filePath)
{
    FILE* file;
    if ((file = fopen(filePath, "r")) == NULL) {
        fprintf(stderr, "Error: File could not open\n");
        exit(1);
    }

    index_t* index = index_new();
    char* currWord;
    int iterator = 0;
    char* word = malloc(100);
    int docID;
    int count;

    while ((currWord = file_readWord(file)) != NULL) {    
        
        // printf("%s", currWord);
        if (iterator == 0) {                                 // at iterator = 0 you are reading a word in
            strcpy(word, currWord);                          // at iterator = 1 you are reading the docID
            iterator = 1;                                    // at iterator = 2 you are reading the count
        }                                           
        else if (strcmp(currWord, "") == 0) {                // iterator only resets to 0 on new lines (when the word appears)
            // printf("\n");
            iterator = 0;
        } 
        else if (iterator == 1) {                            // Iterator moves between 1 and 2 until reset to 0
            docID = atoi(currWord);
            iterator = 2;
        }
        else if (iterator == 2) {
            iterator = 1;
            count = atoi(currWord);
            index_set(index, docID, word, count);
        }
        free(currWord);
    }
    free(word);
    fclose(file);
    return index;
}