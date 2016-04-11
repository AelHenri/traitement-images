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

  int cols_s = pnm_get_width(ims);
  int rows_s = pnm_get_height(ims);

  int cols_d = factor*cols_s;
  int rows_d = factor*rows_s;

  pnm imd = pnm_new(cols_d, rows_d, PnmRawPpm);

  unsigned short *ps = pnm_get_image(ims);
  unsigned short *pd = pnm_get_image(imd);

  fftw_complex *fftw_for;

  fftw_for = forward(rows_s, cols_s, ps);

  for (int i = 0; i < rows_d; ++i)
  {
    for (int j = 0; j < cols_d; ++j)
    {
      for (int k = 0; k < 3; ++k)
      {
        *pd = 0;
        pd++;        
      }
    }
  }

  pd-=cols_d*rows_d*3;

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
