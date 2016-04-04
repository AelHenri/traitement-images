/**
 * @file test-fft.c
 * @brief test the behaviors of functions in fft module
 *
 */
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "fft.h"

/**
 * @brief test the forward and backward functions
 * @param pnm ims, the source image
 * @param char* name, the image file name
 */
 static void
 test_for_backward(pnm ims, char* name)
 {
  /**
   *fprintf(stderr, "test_for_backward: ");
   *(void)ims;
   *(void)name;
   *fprintf(stderr, "OK\n");
   */
   int cols = pnm_get_width(ims);
   int rows = pnm_get_height(ims);

   pnm imd = pnm_new(cols, rows, PnmRawPpm);

   unsigned short *ps = pnm_get_image(ims);
   unsigned short *pd = pnm_get_image(imd);
   fftw_complex *fftw_for;// = (fftw_complex *) fftw_malloc(cols*rows*sizeof(fftw_complex));
   
   fftw_for = forward(rows, cols, ps);
   pd = backward(rows, cols, fftw_for);

   pnm_save(imd, PnmRawPpm, name);

   pnm_free(ims);
   fftw_free(fftw_for);
 }


/**
 * @brief test image reconstruction from of amplitude and phase spectrum
 * @param pnm ims: the source image
 * @param char *name: the image file name
 */
 static void
 test_reconstruction(pnm ims, char* name)
 {
  fprintf(stderr, "test_reconstruction: ");
  (void)ims;
  (void)name;
  fprintf(stderr, "OK\n");
}


/**
 * @brief test construction of amplitude and phase images in ppm files
 * @param pnm ims, the source image
 * @param char* name, the image file name
 */
 static void
 test_display(pnm ims, char* name)
 {
  fprintf(stderr, "test_display: ");
  (void)ims;
  (void)name;
  fprintf(stderr, "OK\n");
}


/**
 * @brief test the modification of amplitude by adding a periodic functions
          on both vertical and horizontal axis, and 
 *        construct output images
 * @param pnm ims, the source image
 * @param char* name, the image file name
 */
 static void
 test_add_frequencies(pnm ims, char* name)
 {
  fprintf(stderr, "test_add_frequencies: ");
  (void)ims;
  (void)name;
  fprintf(stderr, "OK\n");
}

static void 
run(pnm ims, char* name)
{
  test_for_backward(ims, name);
  test_reconstruction(ims, name);
  test_display(ims, name);
  test_add_frequencies(ims, name);
}


void 
usage (char *s)
{
  fprintf(stderr, "Usage: %s <ims> \n", s);
  exit(EXIT_FAILURE);
}

int 
main(int argc, char *argv[])
{
  if (argc != 2)
    usage(argv[0]);
  pnm ims = pnm_load(argv[1]);
  run(ims, argv[1]);

  return EXIT_SUCCESS;
}
