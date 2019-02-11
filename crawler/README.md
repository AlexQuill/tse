##Crawler
### CS50 Lab 3
### Grace Dorgan January 2018

The TSE crawler is a standalone program that crawls the web and retrieves 
webpages starting from a “seed” URL. It parses the seed webpage, extracts any 
embedded URLs, then retrieves each of those pages, recursively, but limiting 
its exploration to a given “depth”.

### Usage

The crawler program can be run with the command line formatted as follows:
crawler seedURL pageDirectory maxDepth
It takes a URL to a "starting web page", the name of a directory to store all
captured html, and a maximum depth the user wishes the crawler to go to when 
finding urls linked to the current page.
It includes the following functions:

```c
/*Main
* the main method begins by checking the validity of all parameters.  After
* that, it creates the hashtable and bag necessary for the alogorithm to 
* look for linked pages to work. Then we  make a webpage for the seedURL, marked* with depth=0
* Now add that page to the bag of webpages to crawl
* Now add that URL to the hashtable of URLs seen
* while making sure there are more webpages to crawl,
* the method extracts a webpage (URL,depth) item from the bag of webpages to be
* crawled
*    Calls webpage_fetch to pause for at least one second and retrieve a 
*    webpage for that URL,
*    use pagesaver to write the webpage to the pageDirectory with a unique 
*    document ID, as described in the Requirements.
*    if the webpage depth is < maxDepth, explore the webpage to find links by 
*    calling pagescanner.
/*
main (int argc, char **argv)

* This function implements a large portion of the logic in scanning a page for
* outgoing links. Specificially, it does the following portion of pseudocode:
* for each extracted URL:
*
* 1.   ‘normalize’ the URL (see below)
* 2.   if that URL is not ‘internal’ (see below), ignore it;
* 3.   try to insert that URL into the hashtable of URLs seen
*  1.      if it was already in the table, do nothing;
*  2.      if it was added to the table,
*    1.        make a new webpage for that URL, at depth+1
*    2.        add the new webpage to the bag of webpages to be crawled
*/
void pagescanner (webpage_t * page, hashtable_t * ht, bag_t * bag)

/*
* This method writes the webpage page to the pageDirectory with a unique 
* document ID, 
* starting with one and incrementing each time the method is called.
*/
void pagesaver (int file_num, char *directory, webpage_t * page)

/* 
* this is a simple method made for deleting strings that are put into the 
* hashtable as items.
*/

void strdelete (void *item)

/*
* a simple method for printing strings in the hashtable for testing purposes
*/
void strprint (FILE * fp, const char *key, void *item);


```

### Assumptions

No assumptions beyond those that are clear from the spec.

### Exit Codes
1- Incorrecct number of parameters  
2- Parameters may be NULL or unusable - refer to associatedd error message
3- Provided directory does not exist or is unwritable
4- Unable to allocate space for a malloc'd variable - refer to error message
5- Seed URL is not internal

### Compilation

To compile, simply `make`.

See [IMPLEMENTATION](IMPLEMENTATION.md) for details of implementation.  
See [TESTING](TESTING.md) for details of testing and an example test run.
