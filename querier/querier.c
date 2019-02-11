#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#include "../libcs50/counters.h"
#include "../common/index.h"
#include "../libcs50/file.h"

/**********************local types**************/
typedef struct twocounters
{
  counters_t *prevCollection;
  counters_t *result;
} twocounters_t;

typedef struct printablescore
{
  int score;
  int doc;
  char *url;
} printablescore_t;

/********************functions*******************/
bool isValidAndOrPattern (char **wordarr, int numwords);
counters_t *getIntersection (index_t * index, counters_t * ctrs, char *word);
char **cleanQuery (char line[], int numwords, int len);
int getNumWords (char **wordarr);
void printCleanQuery (char **wordarr, int len);
counters_t *parseQuery (char **wordarr, index_t * index, int numWords);
counters_t *getUnion (counters_t * ctrs, counters_t * ctrs2);
void unionHelper (void *arg, const int key, int count);
counters_t *getIntersection (index_t * index, counters_t * ctrs, char *word);
void copyCounter (void *arg, const int key, int count);
void intersectionHelper (void *arg, const int key, int count);
void sortHelper (void *arg, const int key, int count);
void countCounters (void *arg, const int key, int count);
void sortResults (counters_t * unsorted, printablescore_t ** scores);
bool isNoSpecialChars (char line[], int len);
int terminateAndCountWords (char line[], int len);
void printResults (printablescore_t ** scores, int size, char *pageDirectory);
void getLargest (void *arg, const int key, int count);

/********************************cleanQuery*************************/
/*this method uses several smaller helper methods to take in a char[]
 * query and return it as a char **, leaving no whiespace and with
 * all characters decapitalized.  If it does not fufill the right
 * and/or patterns, it will return NULL.
 */
char **
cleanQuery (char line[], int numwords, int len)
{
  //this loop inserts null chars and counts words
  //int numwords = terminateAndCountWords (line, len);
  // this loop puts all of the pointers to strings into an array
  char **wordarr = (char **) malloc (numwords * sizeof (char *));
  if (wordarr == NULL)
    {
      fprintf (stderr, "space could not be allocated for wordarr");
      exit (1);
    }
  int pos = 0;
  char *myword;
  for (int i = 0; i <= len; i++)
    {
      if (isalpha (line[i]))
	{
	  myword = &(line[i]);
	  wordarr[pos] = myword;
	  pos++;
	  for (int j = i;; j++)
	    {
	      if (line[j] == '\0')
		{
		  i = j;
		  break;
		}
	    }
	}
    }
  if (isValidAndOrPattern (wordarr, numwords))
    {
      return wordarr;
    }
  else
    {
      return NULL;
    }
}


/**********************isNoSpecialChars*********************/
/*this method returns true if there are no special characters in 
 * the char[] passed in.  a special character is any non-alphabet
 * character.
 */
bool
isNoSpecialChars (char line[], int len)
{
  //this checks to make sure there are no special characters in the query
  for (int i = 0; i < len; i++)
    {
      if (!isalpha (line[i]) && !isspace (line[i]))
	{
	  return false;
	}
      if (isalpha (line[i]))	//if it is a letter, make it lowercase
	{
	  line[i] = tolower (line[i]);
	}
    }
  return true;
}

/**********************terminateAndCountWords******************/
/*this method adds in null characters at all white space in the
 * query, and returns the number of words in it.
 */
int
terminateAndCountWords (char line[], int len)
{
  int numwords = 0;
  for (int i = 0; i < len; i++)
    {
      if (isalpha (line[i]))
	{
	  for (int j = i;; j++)
	    {
	      if (isspace (line[j]) || line[j] == '\0')
		{
		  line[j] = '\0';
		  numwords++;
		  i = j;
		  break;
		}
	    }
	}
    }
  return numwords;
}

/**********************isValidAndOrPatterm*******************/
/*this method returns true if there are no ands/or at the beginning
 * or end of the wordarray, and no adjacent and/ors
 */
bool
isValidAndOrPattern (char **wordarr, int numwords)
{
  if (strcmp (wordarr[0], "or") == 0 || strcmp (wordarr[0], "and") == 0
      || strcmp (wordarr[numwords - 1], "or") == 0
      || strcmp (wordarr[numwords - 1], "and") == 0)
    {
      fprintf (stderr,
	       "Invalid query: and/or must be between two and sequences\n");
      return false;
    }

  for (int pos = 0; pos < numwords - 1; pos++)
    {
      if (strcmp (wordarr[pos], "and") == 0
	  || strcmp (wordarr[pos], "or") == 0)
	{
	  if (strcmp (wordarr[pos + 1], "and") == 0
	      || strcmp (wordarr[pos + 1], "or") == 0)
	    {
	      fprintf (stderr,
		       "Invalid query: and/or cannot be adjacent to each other.");
	      return false;
	    }
	}
    }
  return true;
}

/********************getNumWords*********************/
/*this method returns the number of words in a char ***/
int
getNumWords (char **wordarr)
{
  if (wordarr != NULL)
    {
      int count = 0;
      for (int i = 0; i < sizeof (wordarr) / sizeof (char *); i++)
	{
	  count++;
	}
      return count;
    }
  return -1;
}

/*********************printCleanQuery*****************/
/*this method goes through a char** provided and prints
 * it back out for the user to see.
 */
void
printCleanQuery (char **wordarr, int len)
{
  if (wordarr != NULL)
    {
      char **temp = wordarr;
      for (int i = 0; i < len; i++)
	{
	  printf ("%s ", *temp);
	  temp++;
	}
      printf ("\n");
    }
}
/****************************sortResults***************/
/*this method sorts the counters_t passed in into a printablescore_t
 * based on the count value of each counternode, largest to smallest
 */
void
sortResults (counters_t * unsorted, printablescore_t ** scores)
{
  printablescore_t *large = malloc (sizeof (printablescore_t));
  large->score = 0;
  counters_iterate (unsorted, large, getLargest);
  free(scores[0]);
  scores[0] = large;
  //this sets the first element of the array to the largest value
  //this is important to the way my jank insertion sort works
  counters_iterate (unsorted, scores, sortHelper);	//iterate through and sort
}

/***************************getLargest*****************/
/*a method to be used with counters_iterate that will set 
 * the printablescore_t passed in as arg to a printablescore_t
 * that has the key and count of the counternode with the 
 * largest count
 */
void
getLargest (void *arg, const int key, int count)
{
  printablescore_t *score = arg;
  if (count > score->score)
    {				//if the current count is larger
      score->score = count;	//put that value in the printablescore_t
      score->doc = key;
    }
}

/***************************printResults*****************/
/* A simple method that prints out the sorted results from 
 * a query in the format specified by the Querier reqs.
 * assumes that all the docIDs are real files in the directory.
 */
void
printResults (printablescore_t ** scores, int size, char *pageDirectory)
{
  for (int i = 0; i < size; i++)
    {
      char dir[260];		//make a pathname
      sprintf (dir, "%s/%i", pageDirectory, scores[i]->doc);
      FILE *fp = fopen (dir, "r");
      char *url = readlinep (fp);
      fclose (fp);
      printf ("score %d doc %d: %s\n", scores[i]->score, scores[i]->doc, url);
      free (url);
    }
}

/*********************sortHelper********************/
/*This method is a helper method for sortResults.  It
 * contains most of the logic to carry out an insertion sort.
 * It assumes that the printablescore_t** passed to it
 * has already had it's first value set to the largest count
 * in the counters_t being iterated through
 */
void
sortHelper (void *arg, const int key, int count)
{
  printablescore_t **scores = arg;	//cast this
  int myCount = 0;
  //myCount will become equal to the next empty spot in the array
  printablescore_t **temp = scores;
  int j = 0;
  while (temp[j]->score != -2 && temp[j]->score != INT_MAX)
    {
      myCount++;
      j++;
    }				//this will give us the next empty spot 
  if (myCount != 0 && temp[0]->doc != key)
    //it can't be the very first spot and it can't be the score already inserted at 0
    {
      for (int i = myCount - 1; i > -1; i--)
	{			//go backwards down array
	  if (temp[i]->score > count)
	    {			//if the current value at this spot in the array is larger
	      if (temp[i + 1]->score != -2)
		{		//if we are not at the end of the array
		  temp[i + 1]->score = count;	//copy score
		  temp[i + 1]->doc = key;	//copy docID
		  break;
		}
	    }
	  else			//if the value at the current position in the array is smaller
	    {			//we copy the current one down the line
	      if (temp[i + 1]->score != -2)
		{		//if we are not at the end hitting the sentinel value
		  temp[i + 1]->score = temp[i]->score;	//push the value down the array to make room
		  temp[i + 1]->doc = temp[i]->doc;
		}
	    }
	}
    }

}

/**********************countCounters******************/
/*this method should have an int * passed to it.  it is for 
 * use in counters_iterate and just increments the int*
 * passed to it for each counternode
 */
void
countCounters (void *arg, const int key, int count)
{
  int *mycount = arg;
  *mycount += 1;
}

/********************parseQuery***********************/
/*This method handles all of the logic for ands and ors in
 * a query.  It will make intersections and unions and 
 * then combine them all to return a counters_t of data
 * that satisfies the query.
 */
counters_t *
parseQuery (char **wordarr, index_t * index, int numWords)
{
  counters_t *currAdd = NULL;	//should start out null
  counters_t *currUnion = counters_new ();
  if (wordarr != NULL)
    {
      for (int i = 0; i < numWords; i++)
	{

	  if (strcmp (wordarr[i], "or") == 0)
	    {			//if the word is or
	      
	      currUnion = getUnion (currUnion, currAdd);
	      //get the union of the current union built up and the currAdd 
	      //buffer of the last intersection
	      if(currAdd != NULL){
	        counters_delete (currAdd);	//clean this up
	        currAdd = NULL;	//set it back to NULL

	      }
	    }
	  else if (strcmp (wordarr[i], "and") == 0)	//if the word is and
	    {
	      i++;		//increment to get the actual argument
	      currAdd = getIntersection (index, currAdd, wordarr[i]);
	      //make the currAdd buffer
	    }
	  else			//if the "and" is implicit
	    {
	      currAdd = getIntersection (index, currAdd, wordarr[i]);
	      //make the currAdd buffer
	    }
	}
      if (currAdd != NULL)	//if the intersection buffer is still full
	{
	  currUnion = getUnion (currUnion, currAdd);
	  counters_delete(currAdd);
	  //unionize one last time

	}
      return currUnion;
    }
  return NULL;
}

/**************************getUnion********************/
/*this method will return a unionized counters_t of two
 * existing counters.  If a key exists in one, it will
 * be added to the result.  If it exists in both, the counts 
 * are added together.
 */
counters_t *
getUnion (counters_t * ctrs, counters_t * ctrs2)
{
  if (ctrs2 == NULL)
    {				//if the second counters_t is null, just return the other
      return ctrs;
    }
  else if (ctrs == NULL)
    {				//if the first ctrs is null, copy the second into it
      counters_iterate (ctrs2, ctrs, copyCounter);
      //counters_delete (ctrs2);
      return ctrs;
    }
  else
    {				//otherwise, unionize the two
      counters_iterate (ctrs2, ctrs, unionHelper);
      //counters_delete (ctrs2);
      return ctrs;
    }
}

/***********************unionHelper**********************/
/*this is a helper method for getUnion.*/
void
unionHelper (void *arg, const int key, int count)
{
  counters_t *result = arg;	//cast the argument
  if (counters_get (result, key) != 0)
    {				//if it's in the set
      counters_set (result, key, counters_get (result, key) + count);	//add the scores
    }
  else
    {				//if it's not in the set
      counters_add (result, key);	//add it to the set
      counters_set (result, key, count);	//set the count to what it is for the key
    }
}

/*******r*********************getIntersection******************/
/* this is a method that will return a counters_t object representing
 * the intersection of an already existing counters_t object and a
 * word.  A key must exist in both sets to be put in the result.
 */
//return the counters_t object put into it if word is not in the index
counters_t *
getIntersection (index_t * index, counters_t * ctrs, char *word)
{
  counters_t *secondCtrs = index_find (index, word);
  if (secondCtrs != NULL)
    {
      if (ctrs == NULL)
	{			//if the first counters_t is null, make it and just copy the other counters_t for the word passed in
	  ctrs = counters_new ();
	  counters_iterate (secondCtrs, ctrs, copyCounter);
	  return ctrs;
	}
      twocounters_t *temp = malloc (sizeof (twocounters_t));	//make a twocounters_t object to pass in two counters at once
      if (temp == NULL)		//null check
	{
	  fprintf (stderr,
		   "memory could not be allocated for twocounters_t temp");
	  exit (2);
	}
      temp->prevCollection = ctrs;	//set the one to compare to
      temp->result = counters_new ();	//set the empty set to become new intersection
      counters_iterate (secondCtrs, temp, intersectionHelper);	//call helper
      counters_t *toReturn = temp->result;
      counters_delete(temp->prevCollection);	//clean up
      free (temp);
      return toReturn;
    }
  return ctrs;			//return the counters_t passed in if the word isn't found in the index
}

/**************************intersectionHelper***************/
/*a helper method for getIntersection*/
void
intersectionHelper (void *arg, const int key, int count)
{
  twocounters_t *ctrs = arg;	//cast
  if (counters_get (ctrs->prevCollection, key) != 0)
    {				//if it is found in both sets
      counters_add (ctrs->result, key);	//add it to the result counters
      if (counters_get (ctrs->prevCollection, key) > count)
	{			//depending on which count is smaller
	  counters_set (ctrs->result, key, count);
	}
      else
	{
	  counters_set (ctrs->result, key,
			counters_get (ctrs->prevCollection, key));
	}
    }
}
/*************************copyCounter**********************/
/*this method just allows one to copy all values in one
 * counters_t into another.  to be used with counters_iterate
 */
void
copyCounter (void *arg, const int key, int count)
{
  counters_t *result = arg;
  counters_add (result, key);
  counters_set (result, key, count);
}


/**********************isGoodLength**************/
/*a simple boolean method that returns true if the int
 * passed in is greater than 0
 */
bool
isGoodLength (int len)
{
  if (len > 0)
    {
      return true;
    }
  else
    {
      return false;
    }
}

/*****************main**********************/

int
main (int argc, const char *argv[])
{
	if(argc != 3){
		fprintf(stderr, "Usage: incorrect number of arguments\n");
		exit(1);
	}
  char *pageDirectory = (char *) argv[1];
  char *indexFilename = (char *) argv[2];

  char exdir[260];
  sprintf (exdir, "%s/.crawler", pageDirectory);	//make the path name
  FILE *fi = fopen (exdir, "r");

  if (fi == NULL)
    {				//check to see if file is there
      fprintf (stderr, "This directory does not have a .crawler file in it");
      exit (1);			//if there is no .crawler file, we don't know who made it
    }
  fclose (fi);

  FILE *fp = fopen (indexFilename, "r");
  if (fp == NULL)
    {
      fprintf (stderr, "%s is not a readable file.", indexFilename);
      exit (1);
    }
  int numLines = lines_in_file (fp);
  fclose (fp);
  // index_t *index = index_new (numLines);
  // index_load (indexFilename, index);
  while (!feof (stdin))
    {
      char *query = readlinep (stdin);
      if( query == NULL){
	      break;}
      int len = strlen (query);
      if (isGoodLength (len))
	{
	  if (isNoSpecialChars (query, len))
	    {
	      index_t *index = index_new (numLines);
	      index_load (indexFilename, index);

	      //checks that query is actually existant
	      //also checks to make sure there are no special characters in the query and makes everything lowercase
	      int numwords = terminateAndCountWords (query, len);
	      //this loop inserts null chars and counts words
	      char **cleanquery = cleanQuery (query, numwords, len);
	      printCleanQuery (cleanquery, numwords);
	      counters_t *temp = parseQuery (cleanquery, index, numwords);
	      printf ("\n");
	      index_delete (index);
	      int t = 0;
	      int *numCounters = &t;
	      counters_iterate (temp, numCounters, countCounters);
	      //get the number of counters so we can allocate enought space in array
	      if (*numCounters != 0)
		{
		  printablescore_t **scores = malloc (sizeof (printablescore_t *) * (*numCounters + 1));	//make array
		  int i;
		  for (i = 0; i < *numCounters; i++)
		    {
		      scores[i] = malloc (sizeof (printablescore_t));
		      scores[i]->score = INT_MAX;
		    }		//set these all to INT_MAX so we can tell what's empty
		   scores[i] = malloc(sizeof(printablescore_t));
		   scores[i]->score = -2;
		  //      THIS IS THE PROBLEM
		  sortResults (temp, scores);
		  printResults (scores, *numCounters, pageDirectory);
		  counters_delete(temp);
		  for (i = 0; i <= *numCounters; i++)
		    {
		      free (scores[i]);
		    }
		  free (scores);
		  free(cleanquery);
		  free(query);
		}
	      else
		{
		  printf ("no matches found\n");
		}
	    }
	  else
	    {
	      fprintf (stderr, "this query has a special character, and is invalid. please enter a new query.\n");
	    }
	}
      else
	{
	  printf
	    ("this query has a length of less than 1, and is invalid. please enter a new query");
	}
    }
}
