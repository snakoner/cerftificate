#ifndef __DC_H__
#define __DC_H__

#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <malloc.h>

#define pi 	3.14159265

typedef unsigned char uchar;

//MATRIX OPERATIONS
template < typename Type1, typename Type2 >
float** 	MDot(Type1 **A, Type2 **B);
//DISCRETE COSINE TRANSFORMATION
float** 	GenerateCosineMatrix(void);
template <typename Type>
float**		DiscreteCosineTransformation_Inverse2D(Type **Y, float ** cosine_matrix);
float**		DiscreteCosineTransformation_Forward2D(uchar **X, float ** cosine_matrix);
float* 		DiscreteCosineTransformation_Forward1D(uchar *v);
float* 		DiscreteCosineTransformation_Inverse1D(float *DCT);

#endif