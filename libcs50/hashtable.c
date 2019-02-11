/*
 *
 * see hashtable.h for more information.
 * Grace Dorgan Jan 2018 based off of code by
 * David Kotz, April 2016, 2017
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "hashtable.h"
#include "memory.h"
#include "jhash.h"

/**************** local types ****************
typedef struct hashtable {
  void *item;// pointer to data for this item
  char *key;   
  struct setnode *next;	      // link to next node
} hashtable_t;
*/

/**************** global types ****************/
typedef struct hashtable
{
  set_t **array;		// head of the list of items in set
  int size;
} hashtable_t;

/**************** global functions ****************/
/* that is, visible outside this file */
/* see set.h for comments about exported functions */


/**************** hashtable_new() ****************/
/* Create a new (empty) hashtable; return NULL if error. */
hashtable_t *
hashtable_new (const int num_slots)
{
  hashtable_t *hashtable = malloc (sizeof (hashtable_t));
  //hashtable->array = set_t *array[num_slots];
  if (hashtable == NULL)
    {
      return NULL;		// error allocating set
    }
  else
    {
      // initialize contents of set structure
      hashtable->array = malloc (num_slots * sizeof (set_t *));
      for (int i = 0; i < num_slots; i++)
	{
	  hashtable->array[i] = set_new ();

	}
      hashtable->size = num_slots;
      return hashtable;
    }
}

/**************** hashtable_insert() ****************/
/* Insert item, identified by key (string), into the given hashtable.
 * The key string is copied for use by the hashtable.
 * Return false if key exists in ht, any parameter is NULL, or error;
 * return true iff new item was inserted.
 */
bool
hashtable_insert (hashtable_t * ht, const char *key, void *item)
{
  if (ht != NULL && key != NULL && item != NULL)
    {
	char *copykey = (char *) malloc ((strlen (key) + 1) * sizeof (char));
	if(copykey == NULL){
		fprintf(stderr, "copykey could not be allocated");
		return false;
	}

      //set the hash value
      int hash = JenkinsHash (key, ht->size);
      copykey = (char *) strcpy (copykey, key);//copy the key!!
      if (ht->array[hash] == NULL)
	{
	  ht->array[hash] = set_new ();
	  if (set_insert (ht->array[hash], copykey, item)){
		  free(copykey);//free it right after
	    return true;	//if it works
	  }
	  else{
		  free(copykey);
	    return false;}
	}
      else
	{
	  if (set_insert (ht->array[hash], copykey, item)){
		  free(copykey);
	    return true;}
	  else{
		  free(copykey);
	    return false;}
	}
    }
  else
    {
      return false;
    }
}

/**************hashtable_find********************/
/* Return the item associated with the given key;
 * return NULL if hashtable is NULL, key is NULL, key is not found.
 */
void *
hashtable_find (hashtable_t * ht, const char *key)
{
  if (ht == NULL || key == NULL)
    {
      return NULL;		// bad bag or bad key
    }
  else
    {
      int hash = JenkinsHash (key, ht->size);
      if (ht->array[hash] != NULL)
	{
	  return set_find (ht->array[hash], key);
	}
      else
	{
	  return NULL;
	}
    }
  return NULL;
}

/**************** hashtable_print() ****************/

/* Print the whole table; provide the output file and func to print each item.
 * Ignore if NULL fp. Print (null) if NULL ht.
 * Print a table with no items if NULL itemprint.
 */
void
hashtable_print (hashtable_t * ht, FILE * fp,
		 void (*itemprint) (FILE * fp, const char *key, void *item))
{
  if (fp != NULL)
    {
      if (ht != NULL)
	{
	  fprintf (fp, "Hashtable:\n");
	  for (int i = 0; i < ht->size; i++)
	    {
	      // print this node
	      fprintf (fp, "Bin number %i: ", i);
	      if (itemprint != NULL && ht->array[i] != NULL)
		{		// print the set 
		  set_print (ht->array[i], fp, itemprint);
		  fprintf (fp, "\n");
		}
	    }
	}
      else
	{
	  fputs ("(null)", fp);
	}
    }
}

/**************** hashtable_iterate() ****************/
/* Iterate over all items in the table; in undefined order.
 * Call the given function on each item, with (arg, key, item).
 * If ht==NULL or itemfunc==NULL, do nothing.
 */
void
hashtable_iterate (hashtable_t * ht, void *arg,
		   void (*itemfunc) (void *arg, const char *key, void *item))
{
  if (ht != NULL && itemfunc != NULL)
    {
      // call itemfunc with arg, on each item
      for (int i = 0; i < ht->size; i++)
	{
	  if (ht->array[i] != NULL)
	    {
	      set_iterate (ht->array[i], arg, itemfunc);
	    }
	}
    }
}

/**************** hashtable_delete() ****************/
/* Delete the whole hashtable; ignore NULL ht.
 * Provide a function that will delete each item (may be NULL).
 */
void
hashtable_delete (hashtable_t * ht, void (*itemdelete) (void *item))
{
  for (int i = 0; i < ht->size; i++)
    {
      set_delete (ht->array[i], itemdelete);
    }

  free (ht->array);

  free (ht);
}
