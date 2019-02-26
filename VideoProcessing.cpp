#include <iostream>
#include <stdlib.h>

#define KR	0.299
#define KG	0.587
#define KB	0.114
#define N	10

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

int ScalarQuantization(int X, int QP){
	double Y = (float)X/(float)QP;
	if (Y >=-0.5 && Y <= 0.5)
		return 0;
	else if (Y < 0.5)
		return QP*(int)(Y - 0.499);
	else
		return QP*(int)(Y + 0.499);
}

int ReOrdering(int **arr){
	float **res = (float **)calloc(N, sizeof(float*));
	for(int i=0; i<N; i++)
		res[i] = (float *)calloc(N, sizeof(float));
	return 0;
}

//test
int main(int argc, char const *argv[])
{
	const int colum = 10; 
    const int row   = 10; 
    int array[10][10];
 	int arr[100];
    int x, y, value = 1;
    for (int diag = 0; diag < colum; diag++) 
    {
        if (diag % 2 == 0) 
        {
            x = 0; 
            y = diag; 
            while (y >= 0) 
            {
                array[x][y] = value; 
                value++;
                x++;     // по горизонтали, смещаемся влево
                y--;    // по вертикали, смещаемся вниз
            }
        }
        else // по нечетным диагоналям
        {
            x = diag; // х-координата элемента массива на диагонали - diag
            y = 0; // у-координата первого элемента массива на диагонали - diag
 
            while (x >= 0) // пока x-координата находится в левой части диагонали
            {
                array[x][y] = value; // записать значение в массив
                value++;
                x -= 1;  // по горизонтали, смещаемся вправо
                y +=  1; // по вертикали, смещаемся вверх
            }
        }
    }
 
   for (int ix = 0; ix < row; ix++)
    {
        for (int jx = 0; jx < colum; jx++)
            std::cout << array[ix][jx] << "\t";
        std::cout << std::endl;
    }



    for (int diag = 1; diag < colum; diag++)
    {
        if (diag % 2 == 0) // по четным диагоналям
        {
            x = 9; // х-координата первого элемента массива на диагонали - diag
            y = diag;  // у-координата элемента массива на диагонали - diag
 
            while (y <= 9) // Пока не кончилась диагональ
            {
                array[x][y] = value;
                value++;
                x--; // по горизонтали, смещаемся влево
                y++; // по вертикали, смещаемся вниз
            }
        }
        else // по не четным диагоналям
        {
            x = diag; // х-координата первого элемента к-ой диагонали
            y = 9;  // у-координата первого элемента к-ой диагонали
 
            while (x <= 9) // Пока не кончилась диагональ
            {
                array[x][y] = value;
                value++;
                x++; // по горизонтали, смещаемся вправо
                y--; // по вертикали, смещаемся вверх
            }
        } // конец if-else
    } // конец цикла for (заполнение второй половины массива)
int cnt = 0;

    for (int diag = 0; diag < colum; diag++) 
    {
        cnt++;
        if (diag % 2 == 0) 
        {
            x = 0; 
            y = diag; 
            while (y >= 0) 
            {
                arr[cnt] = array[x][y];
                value++;
                x++;     // по горизонтали, смещаемся влево
                y--;    // по вертикали, смещаемся вниз
            }
        }
        else // по нечетным диагоналям
        {
            x = diag; // х-координата элемента массива на диагонали - diag
            y = 0; // у-координата первого элемента массива на диагонали - diag
 
            while (x >= 0) // пока x-координата находится в левой части диагонали
            {
                arr[cnt] = array[x][y];
                value++;
                x -= 1;  // по горизонтали, смещаемся вправо
                y +=  1; // по вертикали, смещаемся вверх
            }
        }
    }
 
   for (int ix = 0; ix < row; ix++)
    {
        for (int jx = 0; jx < colum; jx++)
            std::cout << array[ix][jx] << "\t";
        std::cout << std::endl;
    }



    for (int diag = 1; diag < colum; diag++)
    {
        if (diag % 2 == 0) // по четным диагоналям
        {
            x = 9; // х-координата первого элемента массива на диагонали - diag
            y = diag;  // у-координата элемента массива на диагонали - diag
 
            while (y <= 9) // Пока не кончилась диагональ
            {
                arr[cnt] = array[x][y];
                value++;
                x--; // по горизонтали, смещаемся влево
                y++; // по вертикали, смещаемся вниз
            }
        }
        else // по не четным диагоналям
        {
            x = diag; // х-координата первого элемента к-ой диагонали
            y = 9;  // у-координата первого элемента к-ой диагонали
 
            while (x <= 9) // Пока не кончилась диагональ
            {
                arr[cnt] = array[x][y];
                value++;
                x++; // по горизонтали, смещаемся вправо
                y--; // по вертикали, смещаемся вверх
            }
        } // конец if-else
    } // конец цикла for (заполнение второй половины массива)



        for (int ix = 0; ix < row; ix++)
            std::cout << arr[ix] << " ";
  

	return 0;
}