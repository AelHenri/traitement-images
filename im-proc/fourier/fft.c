#include <float.h>
#include <stdlib.h>
#include <math.h>

#include "fft.h"

 fftw_complex
  *forward(int rows, int cols, unsigned short* g_img)
  {
    fftw_complex* img_in = (fftw_complex*) fftw_malloc(rows*cols*sizeof(fftw_complex));
    fftw_complex* img_out = (fftw_complex*) fftw_malloc(rows*cols*sizeof(fftw_complex));

    for (int i = 0; i < rows; ++i)
    {
      for (int j = 0; j < cols; ++j)
      {
        *img_in = *g_img + I*0;
        g_img+=3;
        img_in++;
      }
    }
    img_in -= cols*rows;
    fftw_plan p = fftw_plan_dft_2d(rows, cols, img_in, img_out, FFTW_FORWARD, FFTW_ESTIMATE);

    fftw_execute(p);


    fftw_destroy_plan(p);
    fftw_free(img_in);

    return img_out;
  }


  unsigned short 
  *backward(int rows, int cols, fftw_complex* freq_repr)
  {
    unsigned short * img_out = malloc(rows*cols*sizeof(unsigned short)*3);

    fftw_complex* fftw_back = (fftw_complex*) fftw_malloc(rows*cols*sizeof(fftw_complex));
    fftw_plan p = fftw_plan_dft_2d(rows, cols, freq_repr, fftw_back, FFTW_BACKWARD, FFTW_ESTIMATE);
    

    fftw_execute(p);
    fftw_destroy_plan(p);

    for (int i = 0; i < rows; ++i)
    {
      for (int j = 0; j < cols; ++j)
      {
        (*fftw_back)*=(1./(rows*cols));
        for (int k = 0; k < 3; ++k)
        {
         *img_out = (unsigned short) creal(*fftw_back);
         img_out++;
        }
        fftw_back++;
     }
   }
  img_out -= cols*rows*3;
  fftw_back -= cols*rows;


   fftw_free(fftw_back);
   return img_out;
  }

void freq2spectra(int rows, int cols, fftw_complex* freq_repr, float* as, float* ps) 
{
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {

      for (int k = 0; k < 3; ++k)
      {
        *as = sqrtf( creal(*freq_repr)*creal(*freq_repr) + cimag(*freq_repr)*cimag(*freq_repr));
        *ps = atan2f( cimag(*freq_repr), creal(*freq_repr) );
        as++;
        ps++;
      }
      freq_repr++;
    }
  }
  as -= 3*cols*rows;
  ps -= 3*rows*cols;
  freq_repr -= rows*cols;
}


void 
spectra2freq(int rows, int cols, float* as, float* ps, fftw_complex* freq_repr)
{
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      *freq_repr = *as * cos(*ps) + I * *as * sin(*ps);
      freq_repr++;
      as+=3;
      ps+=3;
    }
  }

  as -= 3*cols*rows;
  ps -= 3*rows*cols;
  freq_repr-= cols*rows;
}

