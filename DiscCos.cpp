//#include "DiscreteCosine.h"
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <malloc.h>

#define pi 	3.14159265
#define N 	128

typedef unsigned char uchar;

//MATRIX OPERATIONS
template < typename Type1, typename Type2 >
float** 	MDot(Type1 **A, Type2 **B){
	float **C = (float **)calloc(N, sizeof(float*));
	for(int i=0; i<N; i++)
		C[i] = (float *)calloc(N, sizeof(float));
	for(int i = 0; i < N; i++)
	    for(int j = 0; j < N; j++)
	        for(int k = 0; k < N; k++)
	            C[i][j] += (float)A[i][k] * (float)B[k][j];
    return C;}
float** 	T(float **A){
	float **A_T = (float **)malloc(N*sizeof(float*));
	for(int i=0; i<N; i++)
		A_T[i] = (float *)malloc(N*sizeof(float));
	for(int i=0; i<N; i++)
		for(int j=0; j<N; j++)
			A_T[i][j] = A[j][i];
	return A_T;}

//DISCRETE COSINE TRANSFORMATION
float** 	GenerateCosineMatrix(void){
	float **CosMatrix = (float **)calloc(N, sizeof(float*));
	float tmp_cos;
	for(int i=0; i<N; i++)
		CosMatrix[i] = (float *)calloc(N, sizeof(float));
	for(int i=0; i<N; i++)
		for(int j = 0; j < N; j++){
			tmp_cos = cos((2*j+1)*i*pi/(2*N));
			CosMatrix[i][j] = (i==0)?sqrt(1.0/(float)N)*tmp_cos : sqrt(2.0/(float)N)*tmp_cos;
		}
	return CosMatrix;}

template <typename Type>
float**		DiscreteCosineTransformation_Inverse2D(Type **Y, float ** cosine_matrix){
	return MDot(MDot(T(cosine_matrix), Y), cosine_matrix);}
float**		DiscreteCosineTransformation_Forward2D(uchar **X, float ** cosine_matrix){
	return MDot(MDot(cosine_matrix, X), T(cosine_matrix));}

float* 		DiscreteCosineTransformation_Forward1D(uchar *v){
	float *Lambda_Coeff = (float *)malloc(N * sizeof(float));
	float *DCT_Coeff = (float *)calloc(N, sizeof(float));
	//lambda coefficients
	for(int u = 0; u<N; u++)
		Lambda_Coeff[u] = u? sqrt(2.0/8.0) : sqrt(1.0/8.0);
	//calculate DCT coefficient
	for(int u=0; u<N; u++)
		for(int x = 0; x<N; x++)
			DCT_Coeff[u] += Lambda_Coeff[u] *  cos(pi*u*(2*x + 1)/(2*N)) * (float)v[x];
	free(Lambda_Coeff);
	return DCT_Coeff;}
float* 		DiscreteCosineTransformation_Inverse1D(float *DCT){
	float *Lambda_Coeff = (float *)malloc(N * sizeof(float));
	float *V = (float *)calloc(N, sizeof(float));
	//lambda coefficients
	for(int x = 0; x<N; x++)
		Lambda_Coeff[x] = x? sqrt(2.0/8.0) : sqrt(1.0/8.0);
	for(int x = 0; x < N; x++)
		for(int i = 0; i < N; i++)
			V[x] += DCT[i]*Lambda_Coeff[i]*cos(pi*i*(2*x + 1)/(2*N));
	free(Lambda_Coeff);
	return V;}


//test
int main(int argc, char const *argv[])
{
	int i, j;

	uchar **X;
	X = (uchar **)calloc(N, sizeof(uchar*));
	for(i=0; i<N; i++)
		X[i] = (uchar *)calloc(N, sizeof(uchar));
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			X[i][j] = rand()%255;
		}
	}

	float **cosine_matrix = GenerateCosineMatrix();
	float **Y = DiscreteCosineTransformation_Forward2D(X, cosine_matrix);

	return 0;
}