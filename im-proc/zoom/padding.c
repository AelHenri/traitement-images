/**
 * @file padding.c
 * @author Nolwenn Gangloff & Henri Toussaint
 */

#include <stdlib.h>
#include <stdio.h>
#include <bcl.h>
#include "fft.h"
#include <math.h>


 void process(int factor, char* ims_name,char* imd_name){

  pnm ims = pnm_load(ims_name);

  int cols = pnm_get_width(ims);
  int rows = pnm_get_height(ims);

  int new_cols = factor*cols;
  int new_rows = factor*rows;

  pnm imd = pnm_new(new_cols, new_rows, PnmRawPpm);

  unsigned short *ps_one_c = malloc(rows*cols*sizeof(unsigned short));
  for(int i=0;i<rows;i++)
      for(int j=0;j<cols;j++){
		*ps_one_c = pnm_get_component(ims,i,j,1);
		ps_one_c++;
	}
  ps_one_c -= cols*rows;

  fftw_complex *fftw_for;
  fftw_complex *fftw_center = (fftw_complex*) fftw_malloc(new_rows*new_cols*sizeof(fftw_complex));;

  fftw_for = forward(rows, cols, ps_one_c);
  
  int mn_rows = new_rows/2;
  int mn_cols = new_cols/2;
  
  int m_rows = rows/2;
  int m_cols = cols/2;
  
  for (int i = 0; i < new_rows; ++i)
  {
    for (int j = 0; j < new_cols; ++j)
    {
	  if((i>=(mn_rows-m_rows))&&(i<(mn_rows+m_rows))&&(j>=(mn_cols-m_cols))&&(j<(mn_cols+m_cols))){
		  *fftw_center = *fftw_for;
		  fftw_for++;
	  }
	  else{
		  *fftw_center = 0;
	  }
	  fftw_center++;     	 
    }
  }
    
  fftw_center -= new_rows*new_cols;
  fftw_for -= rows*cols;
 
  unsigned short *out = backward(new_rows, new_cols, fftw_center,factor);
    
    for(int i=0;i<new_rows;i++){
      for(int j=0;j<new_cols;j++){
        for(int c=0; c<3; c++){
          pnm_set_component(imd,i,j,c,*out);
        }
        out++;
      }
    }
    pnm_save(imd, PnmRawPpm, imd_name);
	free(ps_one_c);
	pnm_free(imd);
	pnm_free(ims);
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
