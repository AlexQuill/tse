##Indexer
### CS50 Lab 5
### Grace Dorgan Feb 2018

The TSE indexer is a standalone program that reads the document files produced 
by the TSE crawler, builds an index, and writes that index to a file. Its 
companion, the index tester, loads an index file produced by the indexer and 
saves it to another file.
### Usage

The indexer program can be run with the command line formatted as follows:
./indexer pageDirectory indexFilename
where pageDirectory is the pathname of a directory produced by the Crawler, and
where indexFilename is the pathname of a file into which the index should be 
written; the indexer creates the file (if needed) and overwrites the file 
(if it already exists).

*indexer* has the following main:

```c
/*Main
* the main method begins by checking there are 2 parameters.  After
* that, it reads documents from the pageDirectory, each of which has a unique 
* document ID, wherein
*
*    the document id starts at 1 and increments by 1 for each new page,
*    and the filename is of form pageDirectory/id,
*    and the first line of the file is the URL,
*    and the second line of the file is the depth,
*    and the rest of the file is the page content (the HTML, unchanged).
*
*build an inverted-index data structure mapping from words to (documentID, 
* count) pairs, wherein each count represents the number of occurrences of the 
* given word in the given document. Ignore words with fewer than three 
* characters, and “normalize” the word before indexing. (Here, “normalize” 
* means to convert all letters to lower-case.)
* create a file indexFilename and write the index to that file, in the format 
* described below.
/*
main (int argc, char **argv)
```
*indextest* can be called from the command line with the following arguments:

./indextest oldIndexFilename newIndexFilename
where oldIndexFilename is the name of a file produced by the indexer, and
where newIndexFilename is the name of a file into which the index should be 
written.

*indextest* only has a main, which does the following:
```c
/*
* load the index from the oldIndexFilename into an inverted-index data 
* structure. Create a file newIndexFilename and write the index to that file, 
* in the format described below.
*/
main(int argc, char **argv)
```

### Assumptions

*indexer*:
1. pageDirectory has files named 1, 2, 3, …, without gaps.
2. The content of files in pageDirectory follow the format as defined in the 
specs for crawler.

*indextest*:
1. The content of the index file follows the format specified by the *indexer* 
requirement specs

### Exit Codes
1- Space can't be allocated for a variable  
2- The directory supplied either doesn't have a .crawler file or does not exist

### Compilation

To compile, simply `make`.

See [IMPLEMENTATION](IMPLEMENTATION.md) for details of implementation.  
See [TESTING](TESTING.md) for details of testing and an example test run.

