# CS50 TSE
## Jusung Park (JusungPark6)

See pagedir.h for more details.

### Assumption

1. Mem_alloc allows pagedir_init to create a ./crawler file but not any name longer than that.

2. Mem_alloc for pagedir_save allows us to write onto a file in which the fileopener is pageDirectory/docID. We continue the assumption that maxDepth is within range [0, 10].

### Implementation

1. Followed the implementation guidelines and steps provided on TSE GitHub.