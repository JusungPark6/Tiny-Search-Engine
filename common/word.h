/* Jusung Park
 * CS50 Winter 2023
 * word.h - header file for word.c
 */


#include <stdio.h>
#include <stdbool.h>

/**************** functions ****************/

/**************** main ****************/
/* Parses arguments and initializes normalizeWord
 *   
 */
int main(const int argc, char* argv[]);

/**************** indexBuild ****************/
/* Converts a word to a normalized word (all lowercase)
 *
 * Caller provides:
 *   'word', a non-normalized to be normalized
 * 
 * We return:
 *    a normalized word 
 *    if any trouble is found, print an error to stderr and exit non-zero
 * 
 * We guarantee:
 *   
 * Caller is responsible for:
 *   
 */
char* normalizeWord(char* word);