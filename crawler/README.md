# CS50 TSE
## Jusung Park (JusungPark6)

See pagedir.h for more details.

### Assumption

1. We arbitrarily assume the size of the hashtable is 200 slots.

2. the mem_alloc command for pagedir_save allows us to write onto a file in which the fileopener is pageDirectory/docID. We make the assumption that maxDepth is within range [0, 10].

### Implementation

1. Followed the implementation guidelines as provided on TSE GitHub

### Failures

1. Had to constantly backtrack on where to use char vs void functions, make sure the libraries were included properly,  sort out syntax errors, and make sure memory was being allocated and freed properly throughout the whole running of the program.