#include <iostream>
#include <stdlib.h>
#include <vector>
#define KR	0.299
#define KG	0.587
#define KB	0.114
#define N	4
#define MATRIX_REORDERING_SIZE 2*N*N

typedef unsigned char uchar;

class RGB{
	public:
		uchar R;
		uchar B;
		uchar G;
	RGB(uchar R, uchar G, uchar B){
		this->R = R;
		this->G = G;
		this->B = B;
	}
};
class YCbCr{
	public:
		double Y;
		double Cb;
		double Cr;
	YCbCr(double Y, double Cb, double Cr){
		this->Y = Y;
		this->Cb = Cb;
		this->Cr = Cr;
	}
};
YCbCr RGBToYCbCr(RGB rgb){
	float Y = (float)(0.2989 * rgb.R + 0.5866 * rgb.G + 0.1145 * rgb.B);
	float Cb = (float)(-0.1687 * rgb.R - 0.3313 * rgb.G + 0.5000 * rgb.B);
	float Cr = (float)(0.5000 * rgb.R - 0.4184 * rgb.G - 0.0816 * rgb.B);
	return YCbCr(Y, Cb, Cr);
}

int ScalarQuantization(float X, int QP, bool Multiplier){
	double Y = (float)X/(float)QP;
	if (Y >=-0.5 && Y <= 0.5)
		return 0;
	else if (Y < 0.5)
		return Multiplier? QP*(int)(Y - 0.499):(int)(Y - 0.499);
	else
		return Multiplier? QP*(int)(Y + 0.499):(int)(Y + 0.499);
}


//test
int main(int argc, char const *argv[])
{
	return 0;
}