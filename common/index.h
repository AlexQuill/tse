/* index.h - a header file for 'index' module
 * 
 * this index module is an inverted-index data structure mapping from words to 
 * (documentID, count) pairs, wherein each count represents the number of 
 * occurrences of the given word in the given document.
 *
 * Grace Dorgan, Febuary 2018
 */

#ifndef __INDEX_H
#define __INDEX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "counters.h"
#include "file.h"
#include <stdbool.h>
#include "word.h"

/*****************global types*******************/
typedef struct index index_t;
/******************functions*********************/
/*builds a filled-in index from a directory made from a crawler.  It cycles 
 * through all the files in the provided directory, which it assumes are 
 * labeled by numbers, starting at 1, with no gaps.  It then parses each
 * individual file, ignoring words less than 3 chars and converting all words
 * to lower-case.  The words are inserted into the index structure, and the 
 * count for that docID is incremented.
 */
void index_build (char *directory, index_t * index);
/*This function will either create or overwrite the file directory.  It then 
 * will iterate over the index to print the index with one word per line,
 * followed by (docID count) pairs
 */
void index_save (char *indexFile, index_t * index);
/*loads all index data from file provided into the index provided.  this
 * assumes a non-null, empty index is supplied.  If the file is not 
 * readable or does not exist, it will be ignored.
 */
void index_load(char *oldIndexFilename, index_t *index);
/*create a new, empty index; will exit 1 if error allocating space*/
index_t *index_new (int size);
/*returns counters_t associated w the word entered*/
void *index_find(index_t *index, char *word);
/*frees all memory used by the provided index*/
void index_delete (index_t* index);
#endif // __INDEX_H

