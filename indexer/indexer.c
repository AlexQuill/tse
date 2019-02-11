/*indexer.c - a part of lab 5.*/
#include "../common/index.h"


int
main (int argc, char **argv){
if(argc != 3){
fprintf(stderr, "incorrect number of parameters/n");
exit(3);
}
char *pageDirectory = argv[1];
char *indexFilename = argv[2];

index_t* index = index_new(800);//new index
index_build(pageDirectory, index);
index_save(indexFilename, index);
index_delete(index);
exit(0);
}
