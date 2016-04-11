#include <stdlib.h>
#include <float.h>
#include <math.h>
#include "fft.h"
#define C 3
#define P 0.17
#define PM pnm_maxval
typedef unsigned short US;typedef fftw_complex FC;typedef float F;

void test_for_backward(pnm i){
  fprintf(stderr, "test_for_backward: ");  
  int w=pnm_get_width(i),h=pnm_get_height(i);
  US *c=backward(h,w,forward(h,w,pnm_get_channel(i,NULL,0)));
  pnm d=pnm_new(w,h,PnmRawPpm); for(int i=0;i<C;i++)pnm_set_channel(d,c,i);
  pnm_save(d,PnmRawPpm,"a.ppm"); pnm_free(d); free(c);  
  fprintf(stderr, "OK\n");
}
void test_display(pnm i){
  fprintf(stderr, "test_display: ");
  int w=pnm_get_width(i),h=pnm_get_height(i),s=w*h;
  F *a=malloc(s*sizeof(F)); F *p= malloc(s*sizeof(F));
  FC *f=forward(h,w,pnm_get_channel(i,NULL,0)); freq2spectra(h,w,f,a,p);
  F *pr=a; F m=FLT_MIN; while(s--){F v=*pr++; m=m<v?v:m;}; F k=1.0/m; s=w*h;
  US *ac=malloc(s*sizeof(US));US *pc=ac; pr=a; s=w*h;
  while(s--){F x=k*(*pr++); x=x<0?0:x; x=x>PM?PM:x; *pc++=pow(x,P)*PM;}
  pnm d=pnm_new(w, h, PnmRawPpm); for(int i=0;i<C;i++)pnm_set_channel(d,ac,i);
  pnm_save(d, PnmRawPpm, "b.ppm");
  pnm_free(d); free(a); free(p); free(f); free(ac);
  fprintf(stderr, "OK\n");
}
void run(pnm i){
  test_for_backward(i);
  test_display(i);
}
void usage (char *s){
  fprintf(stderr, "Usage: %s <ims> \n", s); exit(EXIT_FAILURE);
}
int main(int argc, char *argv[]){
  if (argc != 2) usage(argv[0]);
  pnm i=pnm_load(argv[1]);
  run(i);
  pnm_free(i);
  return EXIT_SUCCESS;
}
