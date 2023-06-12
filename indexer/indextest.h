/* Jusung Park
 * CS50 Winter 2023
 * indexer.h - header file for CS50 indexer module
 */

/**************** main() ****************/
/* Parses arguments and initializes other modules
 *
 * Caller provides:
 *  Pathname of a indexFile produced by indexer
 *  Pathname of a indexFile to be created or overwritten
 * We exit nonzero:
 *  If incorrect number of args provided
 */
int main(int argc, char* argv[]);

/**************** indexPage() ****************/
/* Reads an index file and creates an equivalent copy
 *
 * Notes:
 *   uses an "iterator" to keep track of which word is being processed from the index file 
 *  
 */
void createnewIndex(char* oldFilePath, char* newFilePath);