# CS50 TSE
## Jusung Park (JusungPark6)

### indexer

A `indexer` maps from `words` to (`docID`, `count`) pairs, representing the number of occurences of that word in that document. We use a `hashtable` wherein each item is a `counters_t` where we use the docID as key.

### Usage

The *indexer* module, defined in `indexer.h` and implemented in `indexer.c`, implements a hashtable of `set_t**`, and exports the following functions:

```c
bool valid_indexFile(char* indexFilename);
void indexPage(index_t** indexTable, webpage_t* webpageDirectoryID, int docID, char* indexFilename);
void indexBuild(char* pageDirectory, char* indexFilename);
```

### Implementation

We implement this indexer `struct index` containing a pointer to a an hashtable of `struct set` data structures. Each slot was a `struct set` mapping from a key word to a `struct counters` representing the number of occurences of that word in that document.

To insert a new item in the hashtable we find the jenkins hash index for the given key, create a new setnode at that hashtable's index if that setnode is already not created, and insert it at the head of the list.

The `valid_indexFile` method builds an in-memory index from webpage files it finds in the pageDirectory.

The `indexBuild` method builds an in-memory index from webpage files it finds in the pageDirectory.

The `indexPage` method scans a webpage document to add its words to the index.

### Other useful helper modules

The `index` module provides the data structure to represent the in-memory index, and functions to read and write index files;

The `webpage` module provides the data structure to represent webpages, and to scan a webpage for words;

The `pagedir` module provides functions to load webpages from files in the pageDirectory;

The `word` module provides a function to normalize a word.

### Assumptions

No assumptions beyond those that are clear from the design spec.

### Files

* `Makefile` - compilation procedure
* `indexer.h` - the interface
* `indexer.c` - the implementation
* `indextest.c` - unit test driver
* `indextest.h` - unit test driver's interface
* `testing.sh` - script testing file
* `testing.out` - result of `make test &> testing.out`

### Compilation

To compile, simply `make` or `make all` in the indexer directory.

To compile just one, simply `make indexer` or `make indextest`.

### Error handling

The implementation shall use defensive-programming techniques to ensure any out of memory or invalid parameters error is caught and recovered as best possible.

### Testing plan

*Unit testing*. A program `indextest` will serve as a unit test for the index module; it reads an index file into the internal `index` data structure, then writes the index out to a new index file.

*Integration testing*. The `indexer`, as a complete program, will be tested by building an index from a `pageDirectory`, and then the resulting index will be validated by running it through the `indextest` to ensure it can be loaded.

Test indexer with various invalid arguments.

1. Test `indexer` with various invalid arguments.
2. no arguments.
3. one argument.
4. three or more arguments.
5. invalid pageDirectory (non-existent path).
6. invalid pageDirectory (not a crawler directory).
7. invalid indexFile (non-existent path).
8. invalid indexFile (read-only directory).
9. invalid indexFile (existing, read-only file).

Run `indexer` on a variety of pageDirectories and use `indextest` as one means of validating the resulting index.

Run `valgrind` on both `indexer` and `indextest` to ensure no memory leaks or errors.

### Testing

The `indextest.c` program reads an index file into the internal `index` data structure, then writes the index out to a new index file.

To test, simply `make test &> testing.out`.
See `testing.out` for details of testing and an example test run.

Try testing with `MEMTEST` by editing Makefile to turn on that flag and then `make test`.

To test with valgrind, `make valgrind`.