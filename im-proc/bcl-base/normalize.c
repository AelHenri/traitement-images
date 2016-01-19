/**
 * @file normalize.c
 * @author Nolwenn Gangloff & Henri Toussaint
 */

#include <stdlib.h>
#include <stdio.h>
#include <bcl.h>

int max_value(unsigned short * img, int rows, int cols, int num) {
  
  int max = -1;
  int i,j;
  
  for(i=0;i<rows;i++){
	  for(j=0;j<cols;j++){
		  
		  if(img[num]>max){
			  max=img[num];
		  }
		  img=img+3;
	  }
  }
  return max;
}

int min_value(unsigned short * img, int rows, int cols, int num) {
  
  int min = 256;
  int i,j;
  
  for(i=0;i<rows;i++){
	  for(j=0;j<cols;j++){
		  
		  if(img[num]<min){
			  min=img[num];
		  }
		  img=img+3;
	  }
  }
  return min;
}

unsigned int normalize(int i, int j, int max, int min, int maxi, int mini) {
		
}

void  
process(int min, int max, char* ims_name,char* imd_name){
  
  pnm ims = pnm_load(ims_name);

  int rows = pnm_get_width(ims);
  int cols = pnm_get_height(ims);
  
  pnm imd = pnm_new(cols, rows, PnmRawPpm);

  unsigned short *ps = pnm_get_image(ims);
  unsigned short *pd = pnm_get_image(imd);
  
  int i,j;
  unsigned short *image = pnm_get_image(ims);

  printf("%d\n", max_value(ps, rows, cols, 2));
  for(i=0;i<rows;i++){
	  for(j=0;j<cols;j++){
		  ps = image + pnm_offset(ims,i,j);
		  for(int c=0; c<3; c++){
			
		  }
	  }
  }
  
  pnm_save(imd, PnmRawPpm, imd_name);
  pnm_free(imd);
  pnm_free(ims);

}

void 
usage (char *s){
  fprintf(stderr, "Usage: %s <min> <max> <ims> <imd>\n", s);
  exit(EXIT_FAILURE);
}

#define PARAM 4
int 
main(int argc, char *argv[]){
  if (argc != PARAM+1) usage(argv[0]);  
  unsigned int min = atoi(argv[1]);
  unsigned int max = atoi(argv[2]);
  char *ims_name = argv[3];
  char *imd_name = argv[4];
  process(min,max,ims_name,imd_name);
  return EXIT_SUCCESS;
}

