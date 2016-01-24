/**
 * @file move.c
 * @author Nolwenn Gangloff & Henri Toussaint
 */

#include <stdlib.h>
#include <stdio.h>
#include <bcl.h>


void  
process(int dx, int dy, char* ims_name,char* imd_name){
  
  pnm ims = pnm_load(ims_name);

  int cols = pnm_get_width(ims);
  int rows = pnm_get_height(ims);
  
  pnm imd = pnm_new(cols, rows, PnmRawPpm);

  unsigned short *p_ims = pnm_get_image(ims);
  unsigned short *p_imd = pnm_get_image(imd);
  
  unsigned short *images = pnm_get_image(ims);
  unsigned short *imaged = pnm_get_image(imd);
  
  int i,j,k;
  
  for(i=dx;i<rows;i++){
	  for(j=dy;j<cols;j++){
		  p_ims = images + pnm_offset(ims,i-dx,j-dy);
		  p_imd = imaged + pnm_offset(imd,i,j);
		  for(k=0; k<3; k++){
			*p_imd = *p_ims;
			p_imd++;
			p_ims++;
			printf("x : %d et y : %d\n", i-dx,j-dy);
		  }
	  }
  }

  pnm_save(imd, PnmRawPpm, imd_name);
  pnm_free(imd);
  pnm_free(ims);

}

void 
usage (char *s){
  fprintf(stderr, "Usage: %s <dx> <dy> <ims> <imd>\n", s);
  exit(EXIT_FAILURE);
}

#define PARAM 4
int 
main(int argc, char *argv[]){
  if (argc != PARAM+1) usage(argv[0]);  
  unsigned int dx = atoi(argv[1]);
  unsigned int dy = atoi(argv[2]);
  char *ims_name = argv[3];
  char *imd_name = argv[4];
  process(dx,dy,ims_name,imd_name);
  return EXIT_SUCCESS;
}

