# CS50 Lab 3

## Jusung Park (JusungPark6)

### querier

### implementation

This implementation should work under most if not all conditions. There are times where there can be double errors thrown. However, all of the functionality required for us in the REQUIREMENTS.md exist. 

 - Prints document set in decreasing order
 - Supports and over or precedence 
 - Supports and and or operators

One way in which my implementation differs from the recommended is that I use a custom data structure called a query rather than a hashtable. Although runtime may be slower, particularly for the and operation where in queryOperation I iterate through two sets of docID lists for O(n^2) time just for comparing two sets of IDs. This could have been accomplished in O(n) time with a hashmap. However, the query structure allows me to track the total number of IDs without iterating through a whole structure, easily allowing for loops outside with the additional benefit of using index values leveraging the totalIDs and IDs array. 