/**
 * @file padding.c
 * @author Nolwenn Gangloff & Henri Toussaint
 */

#include <stdlib.h>
#include <stdio.h>
#include <bcl.h>
#include "fft.h"


void  
process(int factor, char* ims_name,char* imd_name){
	
	
}

void 
usage (char *s){
  fprintf(stderr, "Usage: %s <factor> <ims> <imd> \n", s);
  exit(EXIT_FAILURE);
}

#define PARAM 3
int 
main(int argc, char *argv[]){
  if (argc != PARAM+1) usage(argv[0]);  
  int factor = atoi(argv[1]);
  char *ims_name = argv[2];
  char *imd_name = argv[3];
    
  process(factor,ims_name,imd_name);
  return EXIT_SUCCESS;
}
