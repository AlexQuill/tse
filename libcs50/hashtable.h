/*hashtable.h - a header file for 'hashtable' module
 *
 * A hashtable is a set of (key,item) pairs. It acts just like a set, but is 
 * far more efficient for large collections. It uses a hashing algorithm to
 * place each item, key pairing in a specific place in the array, then uses
 * sets like buckets to hold them. 
 *
 * Grace Dorgan, January 2018
 * Based off of code written by Dvid Kotz in April 2016, 2017
 */
#ifndef __HASHTABLE_H
#define __HASHTABLE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "memory.h"
#include "jhash.h"

/*******************global types********************/
typedef struct hashtable  hashtable_t; //user can not see this
/********************functions**********************/
/* Create a new (empty) hashtable; return NULL if error. */
hashtable_t *hashtable_new(const int num_slots);

/* Insert item, identified by key (string), into the given hashtable.
 * The key string is copied for use by the hashtable.
 * Return false if key exists in ht, any parameter is NULL, or error;
 * return true iff new item was inserted.
 */
bool hashtable_insert(hashtable_t *ht, const char *key, void *item);

/* Return the item associated with the given key;
 * return NULL if hashtable is NULL, key is NULL, key is not found.
 */
void *hashtable_find(hashtable_t *ht, const char *key);

/* Print the whole table; provide the output file and func to print each item.
 * Ignore if NULL fp. Print (null) if NULL ht.
 * Print a table with no items if NULL itemprint.
 */
void hashtable_print(hashtable_t *ht, FILE *fp,
                     void (*itemprint)(FILE *fp, const char *key, void *item));

/* Iterate over all items in the table; in undefined order.
 * Call the given function on each item, with (arg, key, item).
 * If ht==NULL or itemfunc==NULL, do nothing.
 */
void hashtable_iterate(hashtable_t *ht, void *arg,
               void (*itemfunc)(void *arg, const char *key, void *item) );

/* Delete the whole hashtable; ignore NULL ht.
 * Provide a function that will delete each item (may be NULL).
 */
void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item) );
#endif // __HASHTABLE_H
