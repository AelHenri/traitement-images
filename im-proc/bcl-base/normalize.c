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
  unsigned short *p;
  p = img;
  
  for(i=0;i<rows;i++){
	  for(j=0;j<cols;j++){
		  
		  if(p[num]>max){
			  max=p[num];
		  }
		  p=p+3;
	  }
  }
  return max;
}

int min_value(unsigned short * img, int rows, int cols, int num) {
  
  int min = 256;
  int i,j;
  unsigned short *p;
  p = img;
  
  for(i=0;i<rows;i++){
	  for(j=0;j<cols;j++){
		  
		  if(p[num]<min){
			  min=p[num];
		  }
		  p=p+3;
	  }
  }
  return min;
}

unsigned short normalize(unsigned int pixel, int max, int min, int maxi, int mini) {
  unsigned int res;
  float tmp1,tmp2,tmp3;;
  
  tmp1 = (float) (max-min) / (maxi-mini);
  tmp2 = tmp1*pixel;
  tmp3 = ((min*maxi)-(max*mini))/(maxi-mini);
  res = tmp2 + tmp3;
	return res;
}

void  
process(int min, int max, char* ims_name,char* imd_name){
  
  pnm ims = pnm_load(ims_name);

  int cols = pnm_get_width(ims);
  int rows = pnm_get_height(ims);
  
  pnm imd = pnm_new(cols, rows, PnmRawPpm);

  unsigned short *ps = pnm_get_image(ims);
  unsigned short *pd = pnm_get_image(imd);
  
  int i,j;
  int maxi[3], mini[3];


  //unsigned short *image = pnm_get_image(ims);
  maxi[0] = max_value(ps, rows, cols, 0);
  maxi[1] = max_value(ps, rows, cols, 1);
  maxi[2] = max_value(ps, rows, cols, 2);
  mini[0] = min_value(ps, rows, cols, 0);
  mini[1] = min_value(ps, rows, cols, 1);
  mini[2] = min_value(ps, rows, cols, 2);

  printf("maxi1: %d, maxi2: %d, maxi3: %d\n",maxi[0],maxi[1],maxi[2] );
  printf("mini1: %d, mini2: %d, mini3: %d\n",mini[0],mini[1],mini[2] );
  for(i=0;i<rows;i++){
	  for(j=0;j<cols;j++){
		  for(int c=0; c<3; c++){
        *pd = normalize(*ps, max, min, maxi[c], mini[c]);
        pd++;
        ps++;
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

