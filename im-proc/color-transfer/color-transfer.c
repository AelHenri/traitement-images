/**
 * @file color-transfert
 * @brief transfert color from source image to target image.
 *        Method from Reinhard et al. : 
 *        Erik Reinhard, Michael Ashikhmin, Bruce Gooch and Peter Shirley, 
 *        'Color Transfer between Images', IEEE CGA special issue on 
 *        Applied Perception, Vol 21, No 5, pp 34-41, September - October 2001
 */

#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <bcl.h>

#define D 3

 static float RGB2LMS[D][D] = {
 	{0.3811, 0.5783, 0.0402}, 
 	{0.1967, 0.7244, 0.0782},  
 	{0.0241, 0.1288, 0.8444}
 };

 static float LMS2RGB[D][D] = {
 	{4.4679, -3.5873, 0.1193},
 	{-1.2186, 2.3809, -0.1624},
 	{0.0497, -0.2439, 1.2045}
 }


 void matricialProductD1(float A[][], float B[], float res[]) {
 	float tmp[3];
 	for (int i = 0; i < D; ++i)
 	{
 		res[i] = 0;
 		for (int j = 0; j < D; ++j)
 		{
 			res[i] += A[i][j]*B[j];
 		}
 	}

 }

 void matricialProductDD(float A[][], float B[], float res[]) {
 	float tmp[3];
 	for (int i = 0; i < D; ++i)
 	{
 		for (int j = 0; j < D; ++j)
 		{
 			res[i] = 0;

 			res[i] += A[i][j]*B[j];
 		}
 	}
 }


 static void process(char *ims, char *imt, char* imd){
 	pnm pims = pnm_load(ims);
 	pnm pimt = pnm_load(imt);

 	int cols = pnm_get_width(pimt);
 	int rows = pnm_get_height(pimt);

 	pnm pimd = pnm_new(cols, rows, PnmRawPpm);

 	float* LMSs = malloc(cols * rows * 3 * sizeof(float));

 	for (int i = 0; i < rows; ++i)
 	{
 		for (int j = 0; j < cols; ++j)
 		{
 			for (int k = 0; k < 3; ++k)
 			{
 				*LMS = 0;
 				for (int m = 0; m < 3; ++m)
 				{
 					*LMSs += RGB2LMS[k][m] * (float)pnm_get_component(pims,s, i, j, m)
 				}
 				LMSs++;
 			}
 		}
 	}

 	float tmp;

 	LMS -= cols * rows * 3;

 	for (int i = 0; i < rows; ++i)
 	{
 		for (int j = 0; j < cols; ++j)
 		{
 			for (int k = 0; k < 3; ++k)
 			{
 				for (int m = 0; m < 3; ++m)
 				{
 					tmp += LMS2RGB[k][m] * *LMSs;
 					LMSs++;	
 				}
 				LMSs -= 3;
 				pnm_set_component(pimd, i, j, k, (short) tmp);
 			}
 		}
 	}

 	free(LMS);

 	pnm_save(pimd, PnmRawPpm, imd);
 	pnm_free(pimt);
 	pnm_free(pimd);
 	pnm_free(pims);
 }

 void usage (char *s){
 	fprintf(stderr, "Usage: %s <ims> <imt> <imd> \n", s);
 	exit(EXIT_FAILURE);
 }

#define param 3
 int main(int argc, char *argv[]){
 	if (argc != param+1) 
 		usage(argv[0]);
 	process(argv[1], argv[2], argv[3]);
 	return EXIT_SUCCESS;
 }
