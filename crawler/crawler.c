/*crawler.c - a part of lab 4.  This is the part that will actually do crawler stuff.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bag.h"
#include "webpage.h"
#include "hashtable.h"
#include "pagedir.h"

/*********************constants**********************/
const int NUM_SLOTS = 50;
/*******************functions************************/
void pagescanner (webpage_t * page, hashtable_t * ht, bag_t * bag);
void strdelete (void *item);
void strprint (FILE * fp, const char *key, void *item);
/******************main*************************/
int
main (int argc, char **argv)
{
  int max_depth;		//will get assigned later

  //check the parameters
  if (argc != 4)
    {
      fprintf (stderr, "incorrect number of parameters\n");
      exit (1);
    }
  if (argv[1] == NULL || argv[2] == NULL || argv[3] == NULL)
    {
      fprintf (stderr, "NULL parameters");
      exit (2);			//exit code
    }

  char *page_directory = argv[2];
  printf ("\nbefore pulling int");
//pull integer from third argument, check validity
  if (sscanf (argv[3], "%i", &max_depth) != 1)
    {
      fprintf (stderr, "error - third argument is not an integer");
      exit (2);
    }

  char exdir[260];
  sprintf (exdir, "%s/.crawler", page_directory);	//make the path name
  FILE *fp = fopen(exdir, "w");
  if (fp == NULL)
    {				//check to see if directory is there
      fprintf (stderr,
	       "this directory either does not exist or is not writable\n");
      exit (3);
    }
  fclose(fp);

//make sure this is legitimate
  if (max_depth < 0)
    {
      fprintf (stderr, "maxDepth must be a positive integer");
      exit (2);			//this exit code is for issues with parameters
    }

  char *seed_URL = (char *) malloc ((strlen (argv[1]) + 1) * sizeof (char));	//malloc this
  if (seed_URL == NULL)
    {
      fprintf (stderr, "unable to allocate space for seed_URL\n");
      exit (4);
    }

  seed_URL = (char *) strcpy (seed_URL, argv[1]);	//copy the url to normalize
//  const char *space = "filler";
  hashtable_t *seen;
  bag_t *tocrawl;

  tocrawl = bag_new ();		//create bag
  if (tocrawl == NULL)		//make sure it was allocated ok
    {
      fprintf (stderr, "bag_new failed\n");
      exit (4);
    }
  seen = hashtable_new (NUM_SLOTS);	//create hashtable- this has to be freed later
  if (seen == NULL)		//make sure the memory was allocated
    {
      fprintf (stderr, "hashtable_new failed\n");
      exit (4);
    }
  if (!IsInternalURL(seed_URL))
    {
      fprintf (stderr, "The given URL is not internal\n");
      exit (5);
    }

  webpage_t *start = webpage_new (seed_URL, 0, NULL);
  //make space for the first webpage
  if (start == NULL)
    {
      fprintf (stderr, "space could not be allocated for webpage_t start\n");
      exit (4);
    }
  bag_insert (tocrawl, start);
  char *space = (char *)malloc(7 * sizeof(char));  //for the hashtable
  if(space == NULL){
	  fprintf(stderr, "Space could not be allocated for variable space\n");
	  exit(4);
  }
  sprintf (space, "filler");
  hashtable_insert (seen, webpage_getURL (start), space);
  int curr_file_num = 0;
  webpage_t *curr = bag_extract (tocrawl);
  //start with a page

  while (curr != NULL)		//make sure this isn't null, when it is the bag is empty
    {				//while there are still webpages to look at
      if (!webpage_fetch (curr))
	{
	  //pause a second and grab html
	  fprintf (stderr, "web page [%s] could not be assigned an html\n",
		   webpage_getURL (curr));
	}
      else
	{
	  printf ("%i   Fetched: %s\n", webpage_getDepth (curr),
		  webpage_getURL (curr));
	  curr_file_num++;
	  pagedir_pagesaver (curr_file_num, page_directory, curr);	//pass to page saver to write to file
	}
      if (webpage_getDepth (curr) < max_depth)
	{
	  //if the webpage depth is < maxDepth, explore the webpage to find links:
	  pagescanner (curr, seen, tocrawl);
	}
      webpage_delete (curr);
      curr = bag_extract (tocrawl);	//get a new page
    }

  free(seed_URL);
  bag_delete (tocrawl, *webpage_delete);
  //hashtable_print (seen, stdout, *strprint);
  hashtable_delete (seen, *strdelete);
exit(0);
}

/*********************pagescanner*****************/
void
pagescanner (webpage_t * page, hashtable_t * ht, bag_t * bag)
{
  int pos = 0;
  char *result;
  char *space = "filler";
  printf ("\n%i   scanning: %s\n", webpage_getDepth (page),
	  webpage_getURL (page));

  while ((pos = webpage_getNextURL (page, pos, &result)) > 0)
    {				//go through urls on page
      printf ("%i   Found url: %s\n", webpage_getDepth (page), result);

      //process url
      char *url = calloc (strlen (result) + 1, sizeof (char));
      strcpy (url, result);	//have to make a copy to work with normalizeURL
      if (NormalizeURL (url) && IsInternalURL (url))
	{			//check internal url&& normalize
		char *s2 = (char *)malloc((strlen(space) +1) * sizeof(char));
		s2 = (char *)strcpy(s2, space);
	  if (hashtable_insert (ht, url, s2))
	    {
	      //see if you can insert into ht
	      webpage_t *new =
		webpage_new (url, webpage_getDepth (page) + 1, NULL);
	      if (new != NULL)
		{
		  //make a new webpage for the url
		  bag_insert (bag, new);
		  //insert new page into the bag to be crawled
		  printf ("%i   Added: %s\n", webpage_getDepth (new),
			  webpage_getURL (new));
		}
	    }
	  else
	    {
		    free(s2);
	      printf ("%i   duplicate not added: %s\n",
		      webpage_getDepth (page), url);
	    }
	 
	}
      else
	{
	  printf ("%i   Ignore Extern: %s\n", webpage_getDepth (page), url);
	}
      free(result);//make sure to clean up
      free(url);
    }
//free(space);
}

/*************************strdelete********************/
void
strdelete (void *item)
{
  if (item)
    {
      free (item);
    }
}

/*********************strprint*********************/
void
strprint (FILE * fp, const char *key, void *item)
{
  if (item)
    {
      fprintf (fp, "URL: %s -> %p\n", key, item);
    }
}

/////////////////////////////////////////////////////
/*****************Unit Testing**********************/
/////////////////////////////////////////////////////







