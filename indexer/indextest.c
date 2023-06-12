/* Jusung Park
 * CS50 Winter 2023
 * indexer.c program for CS50 indexer module
 */

#include "../common/index.h"
#include "../libcs50/file.h"

int main(int argc, char* argv[]);
void createnewIndex(char* oldFilePath, char* newFilePath);


/**************** main() ****************/
/* see indextest.h for description */
int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Incorrect number of args");
        exit(1);
    }
    createnewIndex(argv[1], argv[2]);
    return 0;
}

/**************** createnewIndex() ****************/
/* see indextest.h for description */
void
createnewIndex(char* oldFilePath, char* newFilePath)
{
    FILE* old = fopen(oldFilePath, "r");

    index_t* index = index_new();
    char* currWord;
    int iterator = 0;
    char* word = malloc(100);
    int docID;
    int count;

    while ((currWord = file_readWord(old)) != NULL) {    
        
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
    fclose(old);
    indexfile_build(index, newFilePath);
    index_delete(index);
}