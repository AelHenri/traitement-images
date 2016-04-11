/**
 * @file copy.c
 * @author Nolwenn Gangloff & Henri Toussaint
 */

#include <stdlib.h>
#include <stdio.h>
#include <bcl.h>
#include <math.h>


void  
process(int factor, char* ims_name,char* imd_name){
	
	pnm ims = pnm_load(ims_name);
    int cols = pnm_get_width(ims);
    int rows = pnm_get_height(ims);
    
    int news_cols = factor*cols;
    int news_rows = factor*rows;

    pnm imd = pnm_new(news_cols, news_rows, PnmRawPpm);
      
    for(int i=0;i<news_rows;i++){	
      for(int j=0;j<news_cols;j++){  
		for(int k=0; k<3; k++){
			pnm_set_component(imd,i,j,k,pnm_get_component(ims,round(i/factor),round(j/factor),k));
		}
      }
    }
    
	pnm_save(imd, PnmRawPpm, imd_name);
	pnm_free(ims);
	pnm_free(imd);
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
