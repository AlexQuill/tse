##Indexer Implementation
###Grace Dorgan, Feb 2018

####Data Structure
The *index* data structure is made of a *hashtable* containing *counters*.  
Each word found on a webpage acts as the key for the hashtable, and the counters
provide an easy way to store docID, count pairs of how many times the given
word appears in a document/webpage.

####Testing Plan
We will test both *indexer* and *indextest*.  *indextest* will be able to load
an index from a file previously created by a *crawler* and then write that index
to a file.  The original file and the new file createdd by *indextest* should
be the same after they are sorted. In addition to this basic test, we will:
1. Test both programs with various forms of incorrect command-line arguments to
ensure that the parsing of commands is correct
2. Test *indexer* with a directory not made by a crawler
3. Test *indexer* with a non-existant file

