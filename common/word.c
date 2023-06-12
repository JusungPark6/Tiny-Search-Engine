/* Jusung Park
 * CS50 Winter 2023
 * word.c - implements normalizeWord
 */

#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/**************** functions ****************/
char* normalizeWord(char* word);

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
char* normalizeWord(char* word){
	int len = strlen(word);
	int i = 0;
	while (i < len){ //sets the ascii value of code if it's upper case to lower case
			if (word[i] < 91 && word[i] > 64){
					word[i] = word[i] + 32;
			}
			i++; //iterator
	}
	return word;
}