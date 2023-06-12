# CS50 Winter 2023 Querier

## Jusung Park (JusungPark6)

### querier

A `querier` is a standalone program that reads the index file produced by the TSE `indexer`, and page files produced by the TSE `querier`, and answers search queries submitted via *stdin*.

### Usage

The *querier* module, defined in `querier.h` and implemented in `querier.c`, implements a hashtable of `set_t**`, a `struct counters` of *(docID, count)* pairs. and exports the following functions:

```c
bool valid_indexFile(char* indexFilename);
void indexPage(index_t** indexTable, webpage_t* webpageDirectoryID, int docID, char* indexFilename);
void indexBuild(char* pageDirectory, char* indexFilename);
```

### Implementation

We implement this querier containing an index of `struct set` data structures that hold the (docID, count) for each word and a `struct counters` data structure that holds the combined set that satisfies the search query.

The `readQuery` method reads the stdin query, parses the query, and validate the query.

The `buildQuery` method builds a series of counters by parsing through an array of connectors and words and following a specified order of connectors (ANDs and ORs).

The `printQueries` method prints the sorted combined counters onto stdout.

### Other useful helper modules

The `index` module provides the data structure to represent the in-memory index, and functions to read and write index files;

The `pagedir` module provides a function to verify that pageDirectory is a Crawler-produced file;

The `word` module provides a function to normalize a query input.

### Assumptions

No assumptions beyond those that are clear from the design spec.

### Files

* `Makefile` - compilation procedure
* `querier.h` - the interface
* `querier.c` - the implementation
* `testing.sh` - script testing file
* `testing.out` - result of `make test &> testing.out`

### Compilation

To compile, simply `make` in the indexer directory.

### Error handling

The implementation shall use defensive-programming techniques to ensure any out of memory or invalid parameters error is caught and recovered as best possible.

### Testing plan

*Integration testing*. The `querier`, as a complete program, will be tested by comparing various invalid arguments as well as invalid queries.

Test indexer with various invalid arguments.

1. Test `indexer` with various invalid arguments.
2. no arguments.
3. one argument.
4. three or more arguments.
5. invalid pageDirectory (non-existent path).
6. invalid pageDirectory (not a crawler directory).
7. invalid indexFilename (non-existent path).
8. invalid indexFilename (non-readable path).

Run `indexer` on a variety of pageDirectories and indexFilenames.

Run `valgrind` on both `indexer` to ensure no memory leaks or errors.

### Testing

To test, simply `make test &> testing.out`.
See `testing.out` for details of testing and an example test run.

Try testing with `MEMTEST` by editing Makefile to turn on that flag and then `make test`.

To test with valgrind, `make valgrind`.