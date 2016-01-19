/**
 * @file extract-subimage.c
 * @author Nolwenn Gangloff & Henri Toussaint
 * @brief extracte un morceau d'image
 */

#include <stdlib.h>
#include <stdio.h>
#include <bcl.h>

void  
process(int i, int j, int rows, int cols, char* ims_name, char* imd_name){
  
  pnm ims = pnm_load(ims_name);
  pnm imd = pnm_new(cols, rows, PnmRawPpm);

  unsigned short *p1 = pnm_get_image(ims);
  unsigned short *p2 = pnm_get_image(imd);
  
  int k,l;
  unsigned short *image = pnm_get_image(ims);

  for(k=0;k<rows;k++){
	  for(l=0;l<cols;l++){
		  p1 = image + pnm_offset(ims,k+i,l+j);
		  for(int c=0; c<3; c++){
			*p2 = *p1;
			p2++;
			p1++;
		  }
	  }
  }
  
  pnm_save(imd, PnmRawPpm, imd_name);
  pnm_free(imd);
  pnm_free(ims);
}

void 
usage (char *s){
  fprintf(stderr, "Usage: %s <i> <j> <rows> <cols> <ims> <imd>\n", s);
  exit(EXIT_FAILURE);
}

#define PARAM 6
int 
main(int argc, char *argv[]){
  if (argc != PARAM+1) usage(argv[0]);  
  int i = atoi(argv[1]);
  int j = atoi(argv[2]);
  int rows = atoi(argv[3]);
  int cols = atoi(argv[4]);
  char *ims_name = argv[5];
  char *imd_name = argv[6];
  process(i,j,rows,cols,ims_name,imd_name);
  return EXIT_SUCCESS;
}

