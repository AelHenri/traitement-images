/**
 * @file color2mean.c
 * @author Nolwenn Gangloff & Henri Toussaint
 */

#include <stdlib.h>
#include <stdio.h>
#include <bcl.h>

void  
process(char* ims_name,char* imd_name){
  
  pnm ims = pnm_load(ims_name);

  int cols = pnm_get_width(ims);
  int rows = pnm_get_height(ims);
  
  pnm imd = pnm_new(cols, rows, PnmRawPpm);

  unsigned short *ps = pnm_get_image(ims);
  unsigned short *pd = pnm_get_image(imd);
  
  int i,j;
  unsigned short *image = pnm_get_image(ims);


  for(i=0;i<rows;i++){
	  for(j=0;j<cols;j++){
		  ps = image + pnm_offset(ims,i,j);
		  for(int c=0; c<3; c++){
			*pd = (*ps + *(ps+1) + *(ps+2)) / 3;
			pd++;
		  }
	  }
  }
  
  pnm_save(imd, PnmRawPpm, imd_name);
  pnm_free(imd);
  pnm_free(ims);

}

void 
usage (char *s){
  fprintf(stderr, "Usage: %s <ims> <imd>\n", s);
  exit(EXIT_FAILURE);
}

#define PARAM 2
int 
main(int argc, char *argv[]){
  if (argc != PARAM+1) usage(argv[0]);  
  char *ims_name = argv[1];
  char *imd_name = argv[2];
  process(ims_name,imd_name);
  return EXIT_SUCCESS;
}

