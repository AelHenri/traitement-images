#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <bcl.h>

#include "domain.h"

#define M_PI acos(-1.0)

void  
process(char dir,float angle, char* ims_name,char* imd_name){
	
  pnm ims = pnm_load(ims_name);
  
  int cols = pnm_get_width(ims);
  int rows = pnm_get_height(ims);
  
  pnm imd = pnm_new(cols, rows, PnmRawPpm);
  
  for(i=0;i<rowsd-1;i++){
	  
	  for(j=0;j<colsd;j++){
		  p_imd = imaged + pnm_offset(imd,i,j);
		  i_ims = i;
		  j_ims = j - (f1*rowss+f2*i)*tan(f2*rad);
		  
		  if(j_ims>=0 && j_ims<colss-1){
			  for(k=0; k<3; k++){
				  *p_imd=bilinear_interpolation(j_ims,i_ims,ims,k);
				  p_imd++;
			  }
		  }
      }
  }	
	    
  pnm_save(imd, PnmRawPpm, imd_name);
  pnm_free(imd);
  pnm_free(ims);

}

static void usage(char* s){
  fprintf(stderr,"Usage: %s <tx> <ax> <ty> <ay> <ims> <imd>\n",s);
  exit(EXIT_FAILURE);
}

#define PARAM 6
int main(int argc, char* argv[]){
  if(argc != PARAM+1) usage(argv[0]);
  
  float tx = atof(argv[1]);
  float ax = atof(argv[2]);
  float ty = atof(argv[3]);
  float ay = atof(argv[4]);
  char *ims_name = argv[5];
  char *imd_name = argv[6];
  process(tx,ax,ty,ay,ims_name,imd_name);

  return EXIT_SUCCESS;
}
