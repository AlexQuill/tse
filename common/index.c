#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "counters.h"
#include "file.h"
#include <stdbool.h>
#include "word.h"
#include "pagedir.c"

typedef struct index
{
  hashtable_t *ht;
} index_t;

/***************local functions*************/
static void index_add (char *word, int docID, index_t * index);
static bool isFile (char *directory, int docID);
static void counthash_print (void *arg, const char *key, void *item);
static void simplectrsprint (void *arg, const int key, int count);
static void c_delete (void *item);
/***************global functions************/
void index_build (char *directory, index_t * index);
void index_save (char *indexFile, index_t * index);
index_t *index_new (int size);
void *index_find(index_t *index, char *word);
void index_delete (index_t * index);
void index_load(char *oldIndexFilename, index_t *index);
/*******************index_new****************/
index_t *
index_new (int size)
{
  index_t *index = malloc (sizeof (index_t));	//make space
  if (index == NULL)		//null check
    {
      fprintf (stderr, "space could not be allocated for index");
      exit (1);
    }
  index->ht = hashtable_new (size);	//dont need to put anything in yet
  return index;
}
void *
index_find(index_t *index, char *word){
	return hashtable_find(index->ht, word);
}


/***********************index_add****************/
static void
index_add (char *word, int docID, index_t * index)
{
  counters_t *count = hashtable_find (index->ht, word);
  if (count == NULL)
    {				//if the word is not already in the table
      counters_t *nucount = counters_new ();	//make a new counters_t
      if (nucount == NULL)
	{			///null check
	  fprintf (stderr, "space could not be allocated for nucount");
	  exit (1);
	}
      counters_add (nucount, docID);	//add the docID
      hashtable_insert (index->ht, word, nucount);	//insert into hash
    }
  else
    {
      counters_add (count, docID);	//else, just add the docID
    }
}

/********************isFile*****************/
/*
 * really only for seeing if files within a crawler directory exist
 */
static bool
isFile (char *directory, int docID)
{
  char exdir[260];
  sprintf (exdir, "%s/%i", directory, docID);	//make the path name

  FILE *fp = fopen (exdir, "r");

  if (fp == NULL)
    {				//check to see if file is there
      return false;
    }
  fclose (fp);

  return true;			//return true if it exists

}

/*******************index_build*****************/
void
index_build (char *directory, index_t * index)
{
  char exdir[260];
  sprintf (exdir, "%s/.crawler", directory);	//make the path name
  FILE *fp = fopen (exdir, "r");

  if (fp == NULL)
    {				//check to see if file is there
      fprintf (stderr, "This directory does not have a .crawler file in it");
      exit (2);			//if there is no .crawler file, we don't know who made it
    }
  fclose (fp);

  for (int i = 1; isFile (directory, i); i++)
    {				//each file in the directory
      char dir[260];		//make a pathname
      sprintf (dir, "%s/%i", directory, i);
      int pos = 0;
      webpage_t *page = reconstructPage (dir);
      char *result;

      while ((pos = webpage_getNextWord (page, pos, &result)) > 0)
	{
	  char *word = NormalizeWord (result);
	  if (strlen (word) >= 3)
	    {
	      index_add (word, i, index);
	    }
	free(result);
	}
      webpage_delete(page);
      //free (result);
    }
}

/***********************index_load***************/
//assumes non-null index_t
//only loads things into the new index
void 
index_load(char *oldIndexFilename, index_t *index){
	FILE *fp = fopen(oldIndexFilename, "r");
	if (fp != NULL){
		//int size = lines_in_file(fp); do not forget gitignore
		while(!feof(fp)){
			
				char *word = (char*) malloc(260*sizeof(char));
				int docID;
				int count;
				fscanf(fp, "%s ", word);//get the word
				while(fscanf(fp,"%d %d", &docID, &count) == 2){
					//while there are still more pairs to read- infinite loop
					char *ch = (char*) malloc(sizeof(char));
					fscanf(fp,"%c",ch);
					if (*ch == '\n'){
						free(ch);
						break;
					}
					free(ch);
					index_add(word, docID, index);//add the word to the index
					counters_t *c = hashtable_find(index->ht, word);//get the counters_t to set
					counters_set(c, docID, count);//set the value corectly
				}
				free(word);
		}
		fclose(fp);
	}
}

/***********************index_save***************/

void
index_save (char *file, index_t * index)
{
  FILE *fp = fopen (file, "w");	//create the file to be written
  hashtable_iterate (index->ht, fp, counthash_print);	//go over ht
  fclose (fp);			//clean up
}

/*********************counthash_print******************/
/*
 * iterates over counters_t and calls simplectrsprint to print in the format
 * specified by index specs
 */

static void
counthash_print (void *arg, const char *key, void *item)
{
  FILE *fp = arg;		//set output
  counters_t *ctrs = item;
  if (fp != NULL && ctrs != NULL)
    {				//null check
      fprintf (fp, "%s ", key);	//print word
      counters_iterate (ctrs, fp, simplectrsprint);	//go through counters_t and print docID count
      fprintf (fp, "\n");	//new line
    }
}

/*********************simplectrsprint*****************/
/*for use in counthash_print, will print items in a counters_t in format
 * docID count
 */

static void
simplectrsprint (void *arg, const int key, int count)
{
  FILE *fp = arg;
  if (fp != NULL)
    {
      fprintf (fp, "%i %i ", key, count);	//print docID count
    }
}

/*************************index_delete***************/

void
index_delete (index_t * index)
{
  hashtable_delete (index->ht, c_delete);	//delete ht & counters
  free (index);			//get the actual struct
}

/**************************c_delete*****************/

static void
c_delete (void *item)
{
  counters_t *c = item;
  counters_delete (c);
}
