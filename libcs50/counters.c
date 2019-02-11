/* 
 * counters.c - CS50 'counters' module
 *
 * see counters.h for more information.
 * Grace Dorgan Jan 2018 based off of code by
 * David Kotz, April 2016, 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "counters.h"

/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
typedef struct counternode
{
  int key;			// key to this node
  int count;			// counter for this key
  struct counternode *next;	// link to next counternode
} counternode_t;

/**************** global types ****************/
typedef struct counters
{
  struct counternode *head;
} counters_t;

/**************** local functions ****************/
/* not visible outside this file */
static counternode_t *counternode_new (int key);

/**************** counters_new() ****************/
counters_t *
counters_new (void)
{
  counters_t *counters = malloc (sizeof (counters_t));
  if (counters != NULL)
    {
      // initialize contents of counters structure
      counters->head = NULL;
      return counters;
    }				//if it gets here, counters could not be allocated
  return NULL;
}

/**************** counters_add() ****************/
void
counters_add (counters_t * ctrs, const int key)
{
  if (key >= 0 && ctrs != NULL)
    {				//null check
      // Iterate through the list to try to find a matching key.  If found, increment the counter for it
      for (counternode_t * n = ctrs->head; n != NULL; n = n->next)
	{
	  if (n->key == key)
	    {
	      n->count++;
	      return;
	    }
	}
      //If nothing was returned in the loop, the key does not exist
      counternode_t *nu = counternode_new (key);	//make a new node for the new key
      if (nu != NULL)
	{
	  nu->count++;		//add to the count to start it off at one
	  nu->next = ctrs->head;	//point it to the head of the linked list
	  ctrs->head = nu;	//make it the new head
	}
    }
}

/**************** counternode_new ****************/

/* Allocate and initialize a counternode and start it off at 0*/
static counternode_t *		// not visible outside this file
counternode_new (const int key)
{
  counternode_t *n = malloc (sizeof (counternode_t));
  if (n == NULL)
    {
      //memory allocation error
      return NULL;
    }
  else
    {				// set variables of the new node
      n->count = 0;
      n->key = key;
      n->next = NULL;
      return n;
    }
}


/**************** counters_get ****************/
int
counters_get (counters_t * ctrs, const int key)
{
  if (ctrs != NULL && ctrs->head != NULL)
    {				//the counters object exists and is not empty
      for (counternode_t * n = ctrs->head; n != NULL; n = n->next)
	{
	  if (n->key == key)
	    {			//if the node is thee right one
	      return n->count;	//return its value
	    }
	}
    }
  return 0;			//only here if we do not find the node
}

/**************** counters_set() ****************/
void
counters_set (counters_t * ctrs, const int key, int count)
{
  if (key >= 0 && ctrs != NULL && count > 0)
    {
      //look through nodes for the matching key and set count
      for (counternode_t * n = ctrs->head; n != NULL; n = n->next)
	{
	  if (n->key == key)
	    {			//the match
	      n->count = count;
	      return;
	    }
	}
      counternode_t *nu = counternode_new (key);	//only necessary if the key did not exist
      if (nu != NULL)
	{			//the new node was allocated ok
	  nu->count = count;
	  nu->next = ctrs->head;
	  ctrs->head = nu;	//the head is now the new node
	}
    }
}

/**************** counters_print() ****************/
/*prints in format Key: 9key) has a count of: (count), */
void
counters_print (counters_t * ctrs, FILE * fp)
{
  if (fp != NULL)
    {				// ignore null files
      if (ctrs != NULL)
	{
	  fputc ('{', fp);
	  //go through all nodes
	  for (counternode_t * n = ctrs->head; n != NULL; n = n->next)
	    {
	      fprintf (fp, "Key: %d has a count of: %d, ", n->key, n->count);
	    }
	  fprintf (fp, "\b}");
	}
      else
	{			//a null counters object gets printed
	  fputs ("(null)", fp);
	}
    }
}

/**************** counters_iterate() ****************/

void
counters_iterate (counters_t * ctrs, void *arg,
		  void (*itemfunc) (void *arg, const int key, int count))
{
  if (ctrs != NULL && itemfunc != NULL)
    {
      // call itemfunc on each item
      for (counternode_t * n = ctrs->head; n != NULL; n = n->next)
	{
	  (*itemfunc) (arg, n->key, n->count);
	}
    }
}

/**************** counters_delete() ****************/
void
counters_delete (counters_t * ctrs)
{
  if (ctrs != NULL)
    {				//ignore
      for (counternode_t * node = ctrs->head; node != NULL;)
	{
	  counternode_t *next = node->next;	// remember what comes next
	  free (node);		// free the node
	  node = NULL;
	  node = next;		// and move on to next
	}
      free (ctrs);
      // ctrs = NULL;
    }
}
