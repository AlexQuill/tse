/*pagedir.c - used by crawler to write webpages to file, used by indexer to read them.
 */
#include "file.h"
#include "webpage.h"

webpage_t *reconstructPage(char *filename){
	FILE *fp = fopen(filename, "r");
	char *url = readlinep(fp);
	char *numstring = readlinep(fp);
	int depth = 0;
	sscanf(numstring, "%d", &depth);
	free(numstring);
	char *html = readfilep(fp);
	webpage_t *newpage = webpage_new(url, depth, html);
	free(url);
	fclose(fp);
	return newpage;
}

/********pagesaver**************/
//this needs to be moved to a separate module: look at hints and tips
//assumes directory exists and is writable
void
pagedir_pagesaver (int file_num, char *directory, webpage_t * page)
{
  char path_file[260];//add null/overflow check?
  sprintf (path_file, "%s/%i", directory, file_num);    //make the path name
  FILE *fp = fopen (path_file, "w");
  fprintf(fp, "%s\n", webpage_getURL(page));
  fprintf(fp, "%i\n", webpage_getDepth(page));
  fprintf (fp, webpage_getHTML (page)); //print html to new file in dir with unique name
  fclose (fp);
}

