# CS50 TSE Querier

## Design Spec

According to the [Querier Requirements Spec](REQUIREMENTS.md), the TSE *querier* is a standalone program that reads the index file produced by the TSE *indexer*, and page files produced by the TSE *querier*, and answers search queries submitted via stdin.

### User interface

The querier's only interface with the user is on the command-line; it must always have two arguments.

```
querier pageDirectory indexFilename
```

For example, if `letters` is a pageDirectory in `../data`,

``` bash
$ querier ../data/letters ../data/letters.index
```

### Inputs and outputs

**Input**: The querier reads files from a directory by constructing file pathnames from the `pageDirectory` parameter followed by a numeric document ID (as described in the Requirements).

The querier also reads a file from the `indexFilename` parameter to create an `index` data struct.

**Output**: We print a series of docID, their scores, and their URL as described in the requirements.

### Functional decomposition into modules

We anticipate the following modules or functions:

 1. *main*, which parses arguments and initializes other modules;
 2. *createIndexFilenameTable*, which builds an index structure, holding the docID, count for each word in a pageDirectory.
 3. *readQuery*, which reads the stdin query, parses the query, and validate the query, and builds a series of counters by parsing through an array of connectors and words and following a specified order of connectors (ANDs and ORs);
 4. *printQuery*, which prints the sorted combined counters onto stdout.

And some helper modules that provide data structures:

 1. *index*, a module providing the data structure to represent the in-memory index, and functions to read and write index files;
 2. *pagedir*, a module providing a function to verify that pageDirectory is a Crawler-produced file;
 3. *word*, a module providing a function to normalize a query input

### Pseudo code for logic/algorithmic flow

The indexer will run as follows:

    parse the command line, validate parameters, initialize other modules
    call createIndexFilenameTable, with indexFilename, and save that output index

    while query is not EOF:
      receive a query from stdin
      call readQuery, with query, index
      if buildQuery does not exit,
        call printQuery on query

where *createIndexFilenameTable:*

    count the number of lines in a file
    create a new 'hashtable' object with that number of slots
    loop over each line in indexFilename
      create a new 'counters' object
      if successful, 
        parse a docID and count to insert into counters
        continue until end of line
      insert 'counters' object into 'hashtable'
    create a 'indexTable' and set its head to be the 'hashtable'
    return that indexTable

where *readQuery:*

    loop through every word of the query
      put every word and connector into an array

    if the first and last word of query are "and" or "or"
      return false
    loop through the array
      check if they have invalid characters, if yes, return false
    loop through the arrays
      if the word itself and the word afterwards are both "and"/"or"s
      return false
    
    create a results 'counters' object

    loop though the array
      if the next connector is an or,
        connect the word's counters to the results counters with a union connector
    
      else if the next connector is an and, and the previous connector is an or,
        create a temp 'counters' object
        while the next connector is an and,
          create a tempCounter 'counters' object
          if the word is the first word in the temp object,
            connect the temp and tempCounter counters with a union connector
          else,
            connect the temp and tempCounter counters with an intersection connector
        connect the last word with an intersection connector
      
      if the next connector is an and,
        if the word is the first word in the array,
          connect the word's counters to results with a union connector
        else,
          connect the word's counters to results in an intersection connector
      
      connect the last word's counters to results with either an intersection connector or union connector depending on the last connector
    
    return the results counters
  
where *printQueries:*

    sort the results counters
    loop through the sorted counters,
      print according to the Requirements spec.

### Major data structures

The key data structure is the *index*, mapping from *word* to *(docID, #occurrences)* pairs.
The *index* is a *hashtable* keyed by *word* and storing *counters* as items.
The *counters* is keyed by *docID* and stores a count of the number of occurrences of that word in the document with that ID.

Another major data structure is the *counters*, to combine the *counters* data structure found in *index* for individual word according to ANDs and ORs operations.

### Testing plan

*Integration testing*. The *querier*, as a complete program, will be tested by comparing various invalid arguments as well as invalid queries.

Test indexer with various invalid arguments:

1. Test `indexer` with various invalid arguments.
2. no arguments.
3. one argument.
4. three or more arguments.
5. invalid pageDirectory (non-existent path).
6. invalid pageDirectory (not a crawler directory).
7. invalid indexFilename (non-existent path).
8. invalid indexFilename (non-readable path).

Test indexer with various invalid queries:

1. Test `querier` with working parameters and invalid query with "and" as first.
2. Test `querier` with working parameters and invalid query with "and" as last.
3. Test `querier` with working parameters and invalid query with "or" as first.
4. Test `querier` with working parameters and invalid query with "or" as last.
5. Test `querier` with working parameters and invalid query with "or" followed by "or".
6. Test `querier` with working parameters and invalid query with "and" followed by "and".
7. Test `querier` with working parameters and invalid query with "and" followed by "or".
8. Test `querier` with working parameters and invalid query with an non-alphabetical letter.

Run `indexer` on a variety of pageDirectories and indexFilenames.

Run `valgrind` on both `indexer` to ensure no memory leaks or errors.