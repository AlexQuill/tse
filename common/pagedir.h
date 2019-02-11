/*header file for pagedir.c - includes all methods*/

#ifndef __PAGEDIR_H
#define __PAGEDIR_H
 

/*this method reconstructs a webpage_t object from the contents of a file 
 * produced by crawler that represents a webpage. The file must have the first
 * line be the url, second line depth, and the rest the html for the page
 */
webpage_t *reconstructPage(char *filename)

/* assumes directory exists and is writable. This method is used by crawler to 
 * write a webpage to a file. It printd the url as the first line, then the depth,
 * then the html for the page
 */
void
pagedir_pagesaver (int file_num, char *directory, webpage_t * page)
#endif // __PAGEDIR_H
