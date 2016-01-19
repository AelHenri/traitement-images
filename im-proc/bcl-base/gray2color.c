/**
 * @file gray2color.c
 * @author Nolwenn Gangloff & Henri Toussaint
 */

#include <stdlib.h>
#include <stdio.h>
#include <bcl.h>

void  
process(char* ims0_name, char* ims1_name,char* ims2_name,char* imd_name){
  
  pnm ims0 = pnm_load(ims0_name);
  pnm ims1 = pnm_load(ims1_name);
  pnm ims2 = pnm_load(ims2_name);
  
  int rows = pnm_get_width(ims0);
  int cols = pnm_get_height(ims0);
  
  pnm imd = pnm_new(cols, rows, PnmRawPpm);

  unsigned short *p0 = pnm_get_image(ims0);
  unsigned short *p1 = pnm_get_image(ims1);
  unsigned short *p2 = pnm_get_image(ims2);
  unsigned short *pimd = pnm_get_image(imd);
  
  int i,j;
  unsigned short *image0 = pnm_get_image(ims0);
  unsigned short *image1 = pnm_get_image(ims1);
  unsigned short *image2 = pnm_get_image(ims2);

  for(i=0;i<rows;i++){
	  for(j=0;j<cols;j++){
		  p0 = image0 + pnm_offset(ims0,i,j);
		  p1 = image1 + pnm_offset(ims1,i,j);
		  p2 = image2 + pnm_offset(ims2,i,j);

		  *pimd++ = *p0;
		  *pimd++ = *p1;
		  *pimd++ = *p2;
	  }
  }
  
  pnm_save(imd, PnmRawPpm, imd_name);
  pnm_free(imd);
  pnm_free(ims0);
  pnm_free(ims1);
  pnm_free(ims2);
}

void 
usage (char *s){
  fprintf(stderr, "Usage: %s <ims0> <ims1> <ims2> <imd>\n", s);
  exit(EXIT_FAILURE);
}

#define PARAM 4
int 
main(int argc, char *argv[]){
  if (argc != PARAM+1) usage(argv[0]);  
  char *ims0_name = argv[1];
  char *ims1_name = argv[2];
  char *ims2_name = argv[3];
  char *imd_name = argv[4];
    
  process(ims0_name,ims1_name,ims2_name,imd_name);
  return EXIT_SUCCESS;
}

