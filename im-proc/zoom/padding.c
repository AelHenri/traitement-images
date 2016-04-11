/**
 * @file padding.c
 * @author Nolwenn Gangloff & Henri Toussaint
 */

#include <stdlib.h>
#include <stdio.h>
#include <bcl.h>
#include "fft.h"


 void process(int factor, char* ims_name,char* imd_name){

  pnm ims = pnm_load(ims_name);

  int cols = pnm_get_width(ims);
  int rows = pnm_get_height(ims);

  int new_cols = factor*cols;
  int new_rows = factor*rows;

  pnm imd = pnm_new(new_cols, new_rows, PnmRawPpm);

  unsigned short *ps = pnm_get_image(ims);
  unsigned short *pd = pnm_get_image(imd);

  fftw_complex *fftw_for;
  fftw_complex *fftw_center = (fftw_complex*) fftw_malloc(new_rows*new_cols*sizeof(fftw_complex));;

  fftw_for = forward(rows, cols, ps);

  int mn_rows = new_rows/2;
  int mn_cols = new_cols/2;
  
  int m_rows = rows/2;
  int m_cols = cols/2;
  
  printf("plop1\n");
  
  for (int i = 0; i < new_rows; ++i)
  {
    for (int j = 0; j < new_cols; ++j)
    {
	  if((i>=(mn_rows-m_rows))&&(i<=(mn_rows+m_rows))&&(j>=(mn_cols-m_cols))&&(j<=(mn_cols+m_cols))){
		  *fftw_center = *fftw_for;
		  fftw_center++;     
		  fftw_for++;       
	  }
	  else{
		  *fftw_center = 0;
		  fftw_center++;     	 
	  }
    }
  }
  fftw_center -= new_rows*new_cols;
  

  pnm step = pnm_new(new_cols, new_rows, PnmRawPpm);
  unsigned short *st = pnm_get_image(step);
  
   for (int i = 0; i < new_rows; ++i)
   {
    for (int j = 0; j < new_cols; ++j)
    {
	  for (int k = 0; k < 3 ; ++k){
		*st = creal(*fftw_center);
	    st++;
	  }
	  fftw_center++;
    }
  } 
  fftw_center -= new_rows*new_cols;
  st -= new_rows*new_cols*3;

  pnm_save(step, PnmRawPpm, "step.ppm");

  
 

  fftw_center -= new_rows*new_cols;
  unsigned short *out = backward(new_rows, new_cols, fftw_center,factor);
  
  
    for(int i=0;i<new_rows;i++){
      for(int j=0;j<new_cols;j++){

        for(int c=0; c<3; c++){
          *pd = *out;
          pd++;
          out++;
        }
        
      }
    }
    printf("plop3.5\n");

    pd -= 3*new_cols*new_rows;
    out -= 3*new_cols*new_rows;
  
    printf("plop4\n");
    
    pnm_save(imd, PnmRawPpm, imd_name);

    
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
