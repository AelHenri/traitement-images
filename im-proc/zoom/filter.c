/**
 * @file filter.c
 * @author Nolwenn Gangloff & Henri Toussaint
 */

#include <stdlib.h>
#include <stdio.h>
#include <bcl.h>

void  
process(int factor, char* filter_name,char* ims_name, char* imd_name){
	
	
}

void 
usage (char *s){
  fprintf(stderr, "Usage: %s <factor> <filter-name> <ims> <imd> \n", s);
  exit(EXIT_FAILURE);
}

#define PARAM 4
int 
main(int argc, char *argv[]){
  if (argc != PARAM+1) usage(argv[0]);  
  int factor = atoi(argv[1]);
  char *filter_name = argv[2];
  char *ims_name = argv[3];
  char *imd_name = argv[4];
    
  process(factor,ims_name,imd_name);
  return EXIT_SUCCESS;
}
