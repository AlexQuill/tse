#Querier Design Spec
##CS50 Lab 6
###Grace Dorgan Feb 2018

####User Interface
The crawler’s only interface with the user is on the command-line.  It always 
takes two parameters in the following style: 

./querier pageDirectory indexFilename
####Inputs and Outputs
Input: The input is the command line inputs: 
where pageDirectory is the pathname of a directory produced by the Crawler, and
where indexFilename is the pathname of a file produced by the Indexer.

Output:
The cleaned search query is printed out for the user to see again after it has 
been put in.  Then, the rresults of all of the documents that satisfy the query 
are output so the user can see their score, docID and url.

####Pseudo Code for Indexer
    1. Validate command line arguments
    2. load the index from indexFilename into an internal data structure.
    3. read search queries from stdin, one per line, until EOF.
       1.  clean and parse each query according to the syntax described below.
        1. if the query syntax is somehow invalid, print an error message, do not perform the query, and prompt for the next query.
        2. print the ‘clean’ query for user to see.
        3. use the index to identify the set of documents that satisfy the query, as described below.
        4. if the query is empty (no words), print nothing.
        5. if no documents satisfy the query, print No documents match.
        6. otherwise, rank the resulting set of documents according to its score, as described below, and print the set of documents in decreasing rank order; for each, list the score, document ID and URL. (Obtain the URL by reading the first line of the relevant document file from the pageDirectory.)
    4. Exit with zero status when EOF is reached on stdin.
####Major Data Structures
1. *index* of all documents and their words
2. *counters* to represent the unique docIDs and their scores for each word
