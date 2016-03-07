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
 	{0.7071, -0.7071, 0.0}
 };

 static float LAB2LMS[D][D] = {
 	{0.5774, 0.4082, 0.7071},
 	{0.5774, 0.4082, -0.7071},
 	{0.5774, -0.8165, 0.0}
 };

void RGB2LAB(pnm pims, float* LAB, int cols, int rows) {

	float* LMS = malloc(cols * rows * 3 * sizeof(float));
	float tmp;

 	//printf("LMS %p, LAB %p\n",LMS, LAB );
 	for (int i = 0; i < rows; ++i)
 	{
 		for (int j = 0; j < cols; ++j)
 		{
 			for (int k = 0; k < 3; ++k)
 			{
 				*LMS = 0.0;
 				for (int m = 0; m < 3; ++m)
 				{
 					*LMS += RGB2LMS[k][m] * (float)pnm_get_component(pims, i, j, m);
 				}

 				if(*LMS >= 1) {
 					*LMS = log10(*LMS); 					
 				}
 				else if (*LMS < 1){
 					*LMS = 0;
 				}

 				LMS++;
 			}
 		}
 	}
 	
 	LMS -= cols * rows * 3;
 	//printf("LMS %p, LAB %p\n",LMS, LAB );

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
 					tmp += LMS2LAB[k][m] * (*LMS);
 					LMS++;	
 				}
 				LMS -= 3;

 				//tmp = log(tmp);

 				*LAB = tmp;
 				LAB++;
 			}
 			LMS += 3;
 		}
 	}

 	LAB -= cols * rows * 3;
 	LMS -= cols * rows * 3;
 	//printf("LMS %p, LAB %p\n",LMS, LAB );

 	free(LMS);
}

void LAB2RGB(pnm pimd, float* LAB, int cols, int rows) {

	float* LMS = malloc(cols * rows * 3 * sizeof(float));
	float tmp;

	// LAB to LMS
	for (int i = 0; i < rows; ++i)
 	{
 		for (int j = 0; j < cols; ++j)
 		{
 			for (int k = 0; k < 3; ++k)
 			{
 				tmp = 0.0;

 				for (int m = 0; m < 3; ++m)
 				{
 					tmp += LAB2LMS[k][m] * *LAB;
 					LAB++;	
 				}
 				LAB -= 3;

 				//tmp = exp(tmp);
 				tmp = pow(10,tmp);
 				
 				*LMS = tmp;

 				LMS++;
 			}
 			LAB += 3;
 		}
 	}

 	LMS -= cols * rows * 3;
 	LAB -= cols * rows * 3;
 	//printf("LMS %p, LAB %p\n",LMS, LAB );

 	// LMS to RGB
 	for (int i = 0; i < rows; ++i)
 	{
 		for (int j = 0; j < cols; ++j)
 		{
 			for (int k = 0; k < 3; ++k)
 			{
 				tmp = 0.0;
 				for (int m = 0; m < 3; ++m)
 				{
 					tmp += LMS2RGB[k][m] * *LMS;
 					LMS++;	
 				}
 				LMS -= 3;
 				tmp = tmp;
 				if (tmp >= 255.0)
 				{
 					tmp = 255.0;
 				}
 				if (tmp <= 0.0)
 				{
 					tmp = 0.0;
 				}

 				pnm_set_component(pimd, i, j, k, (short) tmp);
 			}
 			LMS += 3;
 		}
 	}

 	//printf("%d %d\n", test, rows*cols);
 	LMS -= cols * rows * 3;
 	//printf("LMS %p, LAB %p\n",LMS, LAB );

 	free(LMS);
}

void mean(float *img, float means[], int cols, int rows) {
	means[0] = 0;
	means[1] = 0;
	means[2] = 0;
	for (int i = 0; i < rows; ++i)
 	{
 		for (int j = 0; j < cols; ++j)
 		{
 			for (int k = 0; k < 3; ++k)
 			{
 				means[k] += *img;
 				img++;
 			}
 		}
 	}

 	img -= cols * rows * 3;

 	for (int i = 0; i < 3; ++i)
 	{
 		means[i] = means[i] / ((float)rows * (float)cols);
 	}
 	//printf("*************MEANS****************\n");

 	/*for (int i = 0; i < 3; ++i)
 	{
 		printf("%d : %f ", i, means[i]);;
 	}
 	printf("\n");*/

}

void standardDeviation(float *img, float deviations[], int cols, int rows) {
	float means[3];
	mean(img, means, cols, rows);

	printf("In deviation computing :\n");
	for (int i = 0; i < 3; ++i)
 	{
 		printf("%f\n", means[i]);;
 	}

 	deviations[0] = 0;
 	deviations[1] = 0;
 	deviations[2] = 0;
	for (int i = 0; i < rows; ++i)
 	{
 		for (int j = 0; j < cols; ++j)
 		{
 			for (int k = 0; k < 3; ++k)
 			{
 				deviations[k] += (*img - means[k]) * (*img - means[k]);
 				img++;
 			}
 		}
 	}

 	img -= cols * rows * 3;
 	//printf("%f\n", deviations[0]);
 	for (int i = 0; i < 3; ++i)
 	{
 		deviations[i] = sqrt(deviations[i]/((float)cols * (float)rows));
 	}

 	//printf("*************DEVIATIONS****************\n");
 	/*for (int i = 0; i < 3; ++i)
 	{
 		printf("%d : %f ", i, deviations[i]);;
 	}
 	printf("\n");*/
}

void colorTransfert(float *LABs, float *LABt, float *LABd, int colst, int rowst, int colss, int rowss) {
	float meanss[3];
	float deviationss[3];
	float meanst[3];
	float deviationst[3];

	mean(LABs, meanss, colss, rowss);
	mean(LABt, meanst, colst, rowst);
	standardDeviation(LABs, deviationss, colss, rowss);
	standardDeviation(LABt, deviationst, colst, rowst);

	printf("In color transfert :\n");
	for (int i = 0; i < 3; ++i)
 	{
 		printf("%f\n", meanst[i]);;
 	}
	/*for (int i = 0; i < 3; ++i) {
		printf("%f %f\n", meanss[i], deviationss[i]);
	}*/

 	//printf("%f\n", *LABs);
	float tmp = 0.0;
	for (int i = 0; i < rowst; ++i)
 	{
 		for (int j = 0; j < colst; ++j)
 		{
 			for (int k = 0; k < 3; ++k)
 			{
 				tmp = *LABt - meanst[k];
 				tmp *= (deviationss[k]/deviationst[k]);

 				tmp = tmp + meanss[k];

 				*LABd = tmp;
 				LABs++;
 				LABt++;
 				LABd++;
 			}
 		}
 	}

 	LABs -= colss * rowss * 3;
 	LABt -= colst * rowst * 3;
 	LABd -= colst * rowst * 3;
}

 static void process(char *ims, char *imt, char* imd){
 	pnm pims = pnm_load(ims);
 	pnm pimt = pnm_load(imt);

 	int colst = pnm_get_width(pimt);
 	int rowst = pnm_get_height(pimt);

 	int colss = pnm_get_width(pims);
 	int rowss = pnm_get_height(pims);

 	pnm pimd = pnm_new(colst, rowst, PnmRawPpm);

 	float * LABs = malloc(colss * rowss * 3 * sizeof(float));
 	float * LABt = malloc(colst * rowst * 3 * sizeof(float));
 	float * LABd = malloc(colst * rowst * 3 * sizeof(float));

 	//printf("LABs %p, LABt %p\n",LABs, LABt);

 	RGB2LAB(pims, LABs, colss, rowss);
 	RGB2LAB(pimt, LABt, colst, rowst);

 	//printf("LABs %p, LABt %p\n",LABs, LABt);
 	colorTransfert(LABs, LABt, LABd, colst, rowst, colss, rowss);
 	//printf("LABs %p, LABt %p\n",LABs, LABt);

 	LAB2RGB(pimd, LABd, colst, rowst);
 	//printf("LABs %p, LABt %p\n",LABs, LABt);

 	free(LABs);
 	free(LABt);
 	free(LABd);

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
