/**
 * @file extract-channel.c
 * @author Nolwenn Gangloff & Henri Toussaint
 */

#include <stdlib.h>
#include <stdio.h>
#include <bcl.h>
#include <assert.h>

void  
process(int num, char* ims_name, char* imd_name){
  
  pnm ims = pnm_load(ims_name);
  
  int cols = pnm_get_width(ims);
  int rows = pnm_get_height(ims);
  
  pnm imd = pnm_new(cols, rows, PnmRawPpm);

  unsigned short *p1 = pnm_get_image(ims);
  unsigned short *p2 = pnm_get_image(imd);
  
  int i,j;
  unsigned short *image = pnm_get_image(ims);

  for(i=0;i<rows;i++){
	  for(j=0;j<cols;j++){
		  p1 = image + pnm_offset(ims,i,j);
		  for(int c=0; c<3; c++){
			*p2 = p1[num];
			p2++;
		  }
	  }
  }
  
  pnm_save(imd, PnmRawPpm, imd_name);
  pnm_free(imd);
  pnm_free(ims);
}

void 
usage (char *s){
  fprintf(stderr, "Usage: %s <num> <ims> <imd>\n", s);
  exit(EXIT_FAILURE);
}

#define PARAM 3
int 
main(int argc, char *argv[]){
  if (argc != PARAM+1) usage(argv[0]);  
  unsigned int num = atoi(argv[1]);
  char *ims_name = argv[2];
  char *imd_name = argv[3];
  
  assert(num<=2);
  
  process(num,ims_name,imd_name);
  return EXIT_SUCCESS;
}

