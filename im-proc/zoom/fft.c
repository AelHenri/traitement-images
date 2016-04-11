#include <stdlib.h>
#include <float.h>
#include <math.h>
#include "fft.h"
#define M pnm_maxval
#define FR FFTW_FORWARD
#define BC FFTW_BACKWARD
#define FE FFTW_ESTIMATE
typedef unsigned short A;typedef int C;typedef float D;typedef void F;
typedef fftw_complex B;typedef fftw_plan E;

F ab(A *a,B *b,C c,C d){
  A *aa=a;B *bb=b;for(C e=0;e<c;e++)for(C f=0;f<d;f++){
      D g=*aa++;g=(e+f)%2?-g:g;*bb++=g;
    }
}
F cd(B *a,A *b,C rows,C cols, int factor){
  C c=rows, d=cols;
  B *aa=a;A *bb=b;
  D h=((float)(factor*factor))/(c*d);
  for(C e=0;e<c;e++)
	for(C f=0;f<d;f++){
      D g=h*creal(*aa++);
      g=(e+f)%2?-g:g;
      g=g<0?0:g;
      g=g>M?M:g;
      *bb++=g;   
    }
}  
F ef(A *a,B *b,C c,C d){ab(a, b, c, d);}
F gh(B *a,A *b,C c,C d,int factor){cd(a, b, c, d,factor);}
B *forward(C a,C b,A *d){
  C c=a*b;B *e=malloc(c*sizeof(B));B *f=malloc(c*sizeof(B));
    
  ef(d,e,a,b);E g=fftw_plan_dft_2d(a,b,e,f,FR,FE);
  fftw_execute(g);fftw_destroy_plan(g);free(e);return f;
}
A *backward(int rows, int cols, B *e,int factor){
  C a=rows,b=cols,c=a*b; B *d=malloc(c*sizeof(B));A *f=malloc(c*sizeof(A));
  E g=fftw_plan_dft_2d(a,b,e,d,BC,FE);fftw_execute(g);
  gh(d,f,a,b,factor);fftw_destroy_plan(g);free(d);return f;
}
F freq2spectra(C a, C b, B *c, D *d, D *e){
  D *f=d;D *g=e;B *h=c;C i=a*b; while(i--){*f++=cabs(*h);*g++=carg(*h++);}
}
