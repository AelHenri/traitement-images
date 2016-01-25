#include <math.h>
#include "domain.h"

unsigned short
bilinear_interpolation(float x, float y, pnm ims, int c)
{
  int i = floor(x);
  int j = floor(y);
  
  float dx = x - j;
  float dy = y - i;

  unsigned short *q = pnm_get_image(ims);

  short inter = (1-dx)*(1-dy)* q[c+pnm_offset(ims, i, j)] + dx*(1-dy)* q[c+pnm_offset(ims, i, j+1)] + (1-dx)*dy* q[c+pnm_offset(ims, i+1, j)] + dx*dy* q[c+pnm_offset(ims, i+1, j+1)];

  return inter;
}

