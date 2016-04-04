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

     fprintf(stderr, "test_for_backward: ");
     int cols = pnm_get_width(ims);
     int rows = pnm_get_height(ims);

     pnm imd = pnm_new(cols, rows, PnmRawPpm);

     unsigned short *ps = pnm_get_image(ims);
     unsigned short *pd = pnm_get_image(imd);

     fftw_complex *fftw_for;
     
     fftw_for = forward(rows, cols, ps);
     unsigned short *out = backward(rows, cols, fftw_for);

    for(int i=0;i<rows;i++){
      for(int j=0;j<cols;j++){
        for(int c=0; c<3; c++){
          *pd = *out;
          pd++;
          out++;
        }
      }
    }

     pnm_save(imd, PnmRawPpm, name);
     fftw_free(fftw_for);
     fprintf(stderr, "OK\n");
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
    int cols = pnm_get_width(ims);
    int rows = pnm_get_height(ims);
    pnm imd = pnm_new(cols, rows, PnmRawPpm);
    unsigned short *ps = pnm_get_image(ims);
    unsigned short *pd = pnm_get_image(imd);
    fftw_complex* fftw_for;
    fftw_for = forward(rows, cols, ps);


    float* freq_as = malloc(rows*cols*3*sizeof(float));
    float* freq_ps = malloc(rows*cols*3*sizeof(float));


    freq2spectra(rows,cols,fftw_for,freq_as,freq_ps);

    fftw_complex* freq_repr = (fftw_complex*) fftw_malloc(rows*cols*sizeof(fftw_complex));
    spectra2freq(rows,cols,freq_as,freq_ps,freq_repr);


    unsigned short *out = backward(rows, cols, freq_repr);
    for(int i=0;i<rows;i++){
      for(int j=0;j<cols;j++){
        for(int c=0; c<3; c++){
          *pd = *out;
          pd++;
          out++;
        }
      }
    }
    char dest_name [20];
    strcpy(dest_name,"FB-ASPS-");
    strcat(dest_name,name);
    pnm_save(imd, PnmRawPpm,dest_name);
    fftw_free(fftw_for);
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
    if (argc != 3)
      usage(argv[0]);
    pnm ims = pnm_load(argv[1]);
    run(ims, argv[2]);

    return EXIT_SUCCESS;
  }
