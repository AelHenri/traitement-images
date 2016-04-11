/**
 * @file filter.c
 * @author Nolwenn Gangloff & Henri Toussaint
 */

#include <stdlib.h>
#include <stdio.h>
#include <bcl.h>
#include <math.h>
#include <string.h>

 float box(float x) {
  if (x >= -0.5 && x < 0.5)
    return 1.0;
  else
    return 0.0;
}

float tent(float x) {
  if (x >= -1.0 && x <= 1.0)
    return 1.0-fabsf(x);
  else
    return 0.0;
}

float bell(float x) {
  if (fabsf(x)<=0.5) 
    return -x*x+3.0/4.0;

  else if (fabsf(x) > 0.5 && fabsf(x) <= 1.5)
    return 0.5 * (fabsf(x) - 1.5)*(fabsf(x) - 1.5);

  else
    return 0.0;
}

float mitch(float x){
  if (x>=-1.0 && x<=1.0)
    return 7.0/6.0*pow(fabsf(x), 3) - 2.0*x*x + 8.0/9.0;

  else if ((x >= -2.0 && x <= -1.0) || (x >= 1 && x <= 2))
    return -7.0/18.0 * pow(fabsf(x), 3) + 2*x*x - 10.0/3.0*fabsf(x) + 16.0/9.0;

  else
    return 0.0;
}

void  
process(int factor, char* filter_name,char* ims_name, char* imd_name){

	pnm ims = pnm_load(ims_name);
  int cols = pnm_get_width(ims);
  int rows = pnm_get_height(ims);

  int new_cols = factor*cols;
  int new_rows = factor*rows;

  pnm imw = pnm_new(new_cols, rows, PnmRawPpm);
  pnm imd = pnm_new(new_cols, new_rows, PnmRawPpm);


  // ===== Columns interpolation ===== 
  for(int i=0;i<rows;i++){  
    for(int j=0;j<new_cols;j++){
      float new_j = (float)j / factor;

      float WF = 0;
      if (strcmp(filter_name, "box")== 0) 
        WF = 0.5;
      else if (strcmp(filter_name, "trent")== 0) 
        WF = 1.0;
      else if (strcmp(filter_name, "bell")== 0) 
        WF = 1.5;
      else if (strcmp(filter_name, "mitch")== 0) 
        WF = 2.0;

      float left = new_j - WF;
      float right = new_j + WF;

      int l_int = floor(left);
      int r_int = floor(right);

      float S = 0.0;

      for (int k=l_int; k <= r_int; k++) {

        float h = 0.0;
        if (strcmp(filter_name, "box")== 0) 
          h = box((float)k-new_j);
        else if (strcmp(filter_name, "trent")== 0) 
          h = tent((float)k-new_j);
        else if (strcmp(filter_name, "bell")== 0) 
          h = bell((float)k-new_j);
        else if (strcmp(filter_name, "mitch")== 0) 
          h = mitch((float)k-new_j);

        if (k<0){
          S += pnm_get_component(ims, i, 0, 0)*h;
        }
        else if (k>=cols){
          S += pnm_get_component(ims, i, cols-1, 0)*h;
        }
        else {
          S += pnm_get_component(ims, i, k, 0)*h;            
        }
      }


      for (int c=0; c<3; c++){
        pnm_set_component(imw, i, j, c, (unsigned short) S);
      }
    }
  }


    // ===== Rows interpolation ===== 
  for(int i=0;i<new_rows;i++){  
    for(int j=0;j<new_cols;j++){
      float new_i = (float) i / factor;

      float WF = 0;
      if (strcmp(filter_name, "box")== 0) 
        WF = 0.5;
      else if (strcmp(filter_name, "trent")== 0) 
        WF = 1.0;
      else if (strcmp(filter_name, "bell")== 0) 
        WF = 1.5;
      else if (strcmp(filter_name, "mitch")== 0) 
        WF = 2.0;

      float above = new_i - WF;
      float below = new_i + WF;

      int a_int = floor(above);
      int b_int = floor(below);

      float S = 0.0;

      for (int k=a_int; k <= b_int; k++) {

        float h = 0.0;
        if (strcmp(filter_name, "box")== 0) 
          h = box((float)k-new_i);
        else if (strcmp(filter_name, "trent")== 0) 
          h = tent((float)k-new_i);
        else if (strcmp(filter_name, "bell")== 0) 
          h = bell((float)k-new_i);
        else if (strcmp(filter_name, "mitch")== 0) 
          h = mitch((float)k-new_i);

        if (k<0){
          S += pnm_get_component(imw, 0, j, 0)*h;
        }
        else if (k>=rows){
          S += pnm_get_component(imw, rows-1, j, 0)*h;
        }
        else {
          S += pnm_get_component(imw, k, j, 0)*h;            
        }
      }

      for (int c=0; c<3; c++){
        pnm_set_component(imd, i, j, c, (unsigned short) S);
      }
    }
  }



  pnm_save(imd, PnmRawPpm, imd_name);
  pnm_free(ims);
  pnm_free(imw);
  pnm_free(imd);

}

void 
usage (char *s){
  fprintf(stderr, "Usage: %s <factor> <filter-name> <ims> <imd> \n", s);
  exit(EXIT_FAILURE);
}

#define PARAM 4
int 
main(int argc, char *argv[]){
  if (argc != PARAM+1) usage(argv[0]);  
  int factor = atoi(argv[1]);
  char *filter_name = argv[2];
  char *ims_name = argv[3];
  char *imd_name = argv[4];

  process(factor,filter_name,ims_name,imd_name);
  return EXIT_SUCCESS;
}
