##Querier
### CS50 Lab 5
### Grace Dorgan Feb 2018

The TSE Querier is a standalone program that reads the index file produced by the TSE Indexer, and page files produced by the TSE Querier, and answers search queries submitted via stdin.
### Usage

The indexer program can be run with the command line formatted as follows:
./querier pageDirectory indexFilename
where pageDirectory is the pathname of a directory produced by the Crawler, and
where indexFilename is the pathname of a file written by indexer

*querier* has the following main methods:

```c
/*Main
* The main begins by validating tha command line parameters to make
* sure they are actual directories/files.  Then, it begins reading
* inut from stdin using a loop.  It checks the query for length and
* for special characters and and/or patterns.  It cleans up the query
* and prints it again for the user to see.  It then must parse through
* the query and identify all documents that satisfy the query.
* these are printed according to the querier requirments spec.
/*
main (int argc, char **argv)

/*this method uses several smaller helper methods to take in a char[]
 * query and return it as a char **, leaving no whiespace and with
 * all characters decapitalized.  If it does not fufill the right
 * and/or patterns, it will return NULL.
 */
char **
cleanQuery (char line[], int numwords, int len)

/*this method returns true if there are no special characters in 
 * the char[] passed in.  a special character is any non-alphabet
 * character.
 */
bool
isNoSpecialChars (char line[], int len)

/*this method adds in null characters at all white space in the
 * query, and returns the number of words in it.
 */
int
terminateAndCountWords (char line[], int len)

/*this method returns true if there are no ands/or at the beginning
 * or end of the wordarray, and no adjacent and/ors
 */
bool
isValidAndOrPattern (char **wordarr, int numwords)

/*this method goes through a char** provided and prints
 * it back out for the user to see.
 */
void
printCleanQuery (char **wordarr, int len)

/*This method handles all of the logic for ands and ors in
 * a query.  It will make intersections and unions and 
 * then combine them all to return a counters_t of data
 * that satisfies the query.
 */
counters_t *
parseQuery (char **wordarr, index_t * index, int numWords)

/*this method sorts the counters_t passed in into a printablescore_t
 * based on the count value of each counternode, largest to smallest
 */
void
sortResults (counters_t * unsorted, printablescore_t **scores)

/*This method is a helper method for sortResults.  It
 * contains most of the logic to carry out an insertion sort.
 * It assumes that the printablescore_t** passed to it
 * has already had it's first value set to the largest count
 * in the counters_t being iterated through
 */
void
sortHelper (void *arg, const int key, int count)

```
### Assumptions

1. pageDirectory has files named 1, 2, 3, …, without gaps.
2. The content of files in pageDirectory follow the format as defined in the 
specs for crawler.
3. The content of the file named by indexFilename follows our Index file format;


### Exit Codes
2- Space can't be allocated for a variable  
1- The directory supplied either doesn't have a .crawler file or does not exist

### Compilation

To compile, simply `make`.

See [IMPLEMENTATION](IMPLEMENTATION.md) for details of implementation.  
See [TESTING](TESTING.md) for details of testing and an example test run.

