/**
 * @file print-ppm.c
 * @brief print to standard output a color ppm file
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

static void
process(int r, int g, int b, int rows, int cols){
  printf("P3\n%d %d\n255\n",cols,rows);
  int i=0;
  int j=0;
  for(i=0;i<cols;i++){
	  for(j=0;j<rows;j++){
		 printf("%d\t%d\t%d\t",r,g,b); 
	  }
	  printf("\n");
  }
}

void 
usage (char *s)
{
  fprintf(stderr,
	  "Usage: %s <r={0,255}> <g={0,255}> <b={0,255}> <rows> <cols>\n",s);
  exit(EXIT_FAILURE);
}

#define PARAMS 5
int 
main(int argc, char *argv[])
{
  if (argc != PARAMS+1){
    usage(argv[0]);
  }
    
  unsigned int r=atoi(argv[1]);
  unsigned int g=atoi(argv[2]);
  unsigned int b=atoi(argv[3]);
  unsigned int rows=atoi(argv[4]);
  unsigned int cols=atoi(argv[5]);
  assert(r<=255);
  assert(g<=255);
  assert(b<=255);
    
  process(r, g, b, rows, cols);
  return EXIT_SUCCESS;
}


