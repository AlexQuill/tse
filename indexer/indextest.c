/*indextest.c - a a part of Lab5*/
#include "../common/index.h"

int
main (int argc, char **argv)
{
  if (argc != 3)//cheack params
    {
      fprintf (stderr, "incorrect number of parameters/n");
      exit (3);
    }
char *oldIndexFilename = argv[1];
char *newIndexFilename = argv[2];
FILE *fp = fopen(oldIndexFilename, "r");
if(fp == NULL){//checck to make sure this is a legitimate file
	fprintf (stderr, "The first argument is not a readable file or does not exist");
	exit (4);
}
int size = lines_in_file(fp);//get the size of the file
fclose(fp);
index_t *index = index_new(size);//make the index that size
printf("after index new\n");
index_load(oldIndexFilename, index);//load into the data structure
printf("after index load\n");
index_save(newIndexFilename, index);//write it to a file
index_delete(index);
}
