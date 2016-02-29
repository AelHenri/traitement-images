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
 };

 static float LMS2LAB[D][D] = {
 	{0.5774, 0.5774, 0.5774},
 	{0.4082, 0.4082, -0.8165},
 	{0.7071, -0.4082, 0.0}
 };

 static float LAB2LMS[D][D] = {
 	{0.5774, 0.4082, 0.7071},
 	{0.5774, 0.4082, -0.7071},
 	{0.5774, 0.8165, 0.0}
 };


 static void process(char *ims, char *imt, char* imd){
 	pnm pims = pnm_load(ims);
 	pnm pimt = pnm_load(imt);

 	int cols = pnm_get_width(pimt);
 	int rows = pnm_get_height(pimt);

 	pnm pimd = pnm_new(cols, rows, PnmRawPpm);

 	float* LMSs = malloc(cols * rows * 3 * sizeof(float));
 	float* LABs = malloc(cols * rows * 3 * sizeof(float));

 	printf("LMS %p, LAB %p\n",LMSs, LABs );
 	for (int i = 0; i < rows; ++i)
 	{
 		for (int j = 0; j < cols; ++j)
 		{
 			for (int k = 0; k < 3; ++k)
 			{
 				*LMSs = 0.0;
 				for (int m = 0; m < 3; ++m)
 				{
 					*LMSs += RGB2LMS[k][m] * (float)pnm_get_component(pims, i, j, m);
 				}
 				LMSs++;
 			}
 		}
 	}

 	float tmp;
 	LMSs -= cols * rows * 3;
 	printf("LMS %p, LAB %p\n",LMSs, LABs );


 	//LMStoLAB
 	for (int i = 0; i < rows; ++i)
 	{
 		for (int j = 0; j < cols; ++j)
 		{
 			for (int k = 0; k < 3; ++k)
 			{
 				tmp = 0.0;
 				for (int m = 0; m < 3; ++m)
 				{
 					tmp += LMS2LAB[k][m] * *LMSs;
 					LMSs++;	
 				}
 				LMSs -= 3;

 				*LABs = tmp;
 				LABs++;
 			}
 			LMSs += 3;
 		}
 	}

 	LABs -= cols * rows * 3;
 	LMSs -= cols * rows * 3;
 	printf("LMS %p, LAB %p\n",LMSs, LABs );

 	//LABtoLMS
 	for (int i = 0; i < rows; ++i)
 	{
 		for (int j = 0; j < cols; ++j)
 		{
 			for (int k = 0; k < 3; ++k)
 			{
 				tmp = 0.0;
 				for (int m = 0; m < 3; ++m)
 				{
 					tmp += LAB2LMS[k][m] * *LABs;
 					LABs++;	
 				}
 				LABs -= 3;

 				*LMSs = tmp;
 				LMSs++;
 			}
 			LABs += 3;
 		}
 	}

 	LMSs -= cols * rows * 3;
 	LABs -= cols * rows * 3;
 	printf("LMS %p, LAB %p\n",LMSs, LABs );

 	
 	for (int i = 0; i < rows; ++i)
 	{
 		for (int j = 0; j < cols; ++j)
 		{
 			for (int k = 0; k < 3; ++k)
 			{
 				tmp = 0.0;
 				for (int m = 0; m < 3; ++m)
 				{
 					tmp += LMS2RGB[k][m] * *LMSs;
 					LMSs++;	
 				}
 				LMSs -= 3;
 				if (tmp >= 255)
 					tmp = 255;
 				pnm_set_component(pimd, i, j, k, (short) tmp);
 			}
 			LMSs += 3;
 		}
 	}

 	LMSs -= cols * rows * 3;
 	printf("LMS %p, LAB %p\n",LMSs, LABs );

 	free(LMSs);
 	free(LABs);

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
