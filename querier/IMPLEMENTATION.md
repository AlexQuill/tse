##Indexer Implementation
###Grace Dorgan, Feb 2018

####Data Structures
The *counters* data structure was very useful in this program.  They are easy to use by using the key as the docID and the count as the score, computed by
parsing the query and looking at the number of times a word appeared in a
document.
The *index* data structure also was key, because without it we wouldn't be 
have any access or storage of numbers of times a word appeared in a document.
####Testing Plan
I will test Querier using the following plan:
1. test with various faulty command line arguments:
  1. a non-crawler directory
2. test empty line query
3. test query that I know will have no matches
4. test a query, then test it unioning with another query using or
5. test a query, then test it with and another query
6. fuzz test
