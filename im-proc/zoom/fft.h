/**
 * @file fft.h
 * @brief header for fft module that implements functions for Fourier direct
 *        and inverse transforms and, amplitude and phase spectrum        
 */

#ifndef FFT_H
#define FFT_H

#include <complex.h>
#include <fftw3.h>
#include <bcl.h>

extern fftw_complex 
*forward(int rows, int cols, unsigned short *gray_image);

extern unsigned short 
*backward(int rows, int cols, fftw_complex *freq_repr);

extern void 
freq2spectra(int rows, int cols, fftw_complex *freq_repr, float *as, float *ps);

#endif /* FFT_H */
