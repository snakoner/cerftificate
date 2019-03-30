#ifndef _ARITHM_CODING__
#define _ARITHM_CODING__

#include <iostream>
#include <map>
#include <algorithm> 
#include <vector>
#include <bitset>
#include <cstdlib>
#include <string>
#include <math.h>

#define TRAILING_ONES_LIMITS 	4
#define ZEROS_LEFT_LIMITS		14
#define MB_SIZE 				4
#define N						4
#define MATRIX_REORDERING_SIZE 	2*N*N
#define TOTAL_ZEROS_LIMITS		15
#define COEFF_TOKEN_TABLE_SIZE	136
#define	RUN_BEFORE_TABLE_SIZE	210
#define TOTAL_ZEROS_TABLE_SIZE	480

//#define and 					&&
//#define or 						||

//decimal tables

const uint8_t Decimal_Table_CoeffToken02[COEFF_TOKEN_TABLE_SIZE]{
	 0,1, 0,0, 0,0, 0,0,
	 3,5, 1,1, 0,0, 0,0,
	 5,7, 3,4, 2,1, 0,0,
	 6,7, 5,6, 4,5, 3,3,
	 7,7, 6,6, 5,5, 4,3,
	 8,7, 7,6, 6,5, 4,4,
	 9,15, 8,6, 7,5, 5,4,
	 9,11, 9,14, 8,5, 6,4,
	 9,8, 8,10, 9,13, 7,4,
	 10,15, 10,14, 9,9, 8,4,
	 10,11, 10,10, 10,13, 9,12,
	 11,15, 11,14, 10,9, 10,12,
	 11,11, 11,10, 11,13, 10,8,
	 12,15, 14,1, 11,9, 11,12,
	 12,11, 12,14, 12,13, 11,8,
	 13,7, 12,10, 12,9, 12,12,
	 13,4, 13,6, 13,5, 12,8};
const uint8_t Decimal_Table_CoeffToken24[COEFF_TOKEN_TABLE_SIZE]{
	0,3, 0,0, 0,0, 0,0,
	2,11, 0,2, 0,0, 0,0,
	3,7, 2,7, 1,3, 0,0,
	4,7, 2,10, 2,9, 1,5,
	5,7, 3,6, 3,5, 1,4,
	5,4, 4,6, 4,5, 2,6,
	6,7, 5,6, 5,5, 2,8,
	7,15, 6,6, 6,5, 3,4,
	7,11, 7,14, 7,13, 4,4,
	8,15, 7,10, 7,9, 6,4,
	8,11, 8,14, 8,13, 7,12,
	8,8, 8,10, 8,9, 7,8,
	9,15, 9,14, 9,13, 8,12,
	9,11, 9,10, 9,9, 9,12,
	10,7, 10,11, 10,6, 9,8,
	10,9, 10,8, 10,10, 12,1,
	11,7, 11,6, 11,5, 11,4};
const uint8_t Decimal_Table_CoeffToken48[COEFF_TOKEN_TABLE_SIZE]{
 0,15, 0,0, 0,0, 0,0,
 2,15, 0,14, 0,0, 0,0,
 2,11, 1,15, 0,13, 0,0,
 2,8, 1,12, 1,14, 0,12,
 3,15, 1,10, 1,11, 0,11,
 3,11, 1,8, 1,9, 0,10,
 3,9, 2,14, 2,13, 0,9,
 3,8, 2,10, 2,9, 0,8,
 4,15, 3,14, 3,13, 1,13,
 4,11, 4,14, 3,10, 2,12,
 5,15, 4,10, 4,13, 3,12,
 5,11, 5,14, 4,9, 4,12,
 5,8, 5,10, 5,13, 4,8,
 6,13, 6,7, 5,9, 5,12,
 6,9, 6,12, 6,11, 6,10,
 7,5, 6,8, 7,7, 7,6,
 9,1, 7,4, 8,3, 8,2};
const uint8_t Decimal_Table_CoeffToken8[COEFF_TOKEN_TABLE_SIZE]{
	 4,3, 0,0, 0,0, 0,0,
	 6,0, 5,1, 0,0, 0,0,
	 3,4, 3,5, 3,6, 0,0,
	 2,8, 2,9,  2,10, 2,11,
	 2,12, 2,13, 2,14, 2,15,
	 1,16, 1,17, 1,18, 1,19,
	 1,20, 1,21, 1,22, 1,23,
	 1,24, 1,25, 1,26, 1,27,
	 1,28, 1,29, 1,30, 1,31,
	 0,32, 0,33, 0,34, 0,35,
	 0,36, 0,37, 0,38, 0,39,
	 0,40, 0,41, 0,42, 0,43,
	 0,44, 0,45, 0,46, 0,47,
	 0,48, 0,49, 0,50, 0,51,
	 0,52, 0,53, 0,54, 0,55,
	 0,56, 0,57, 0,58, 0,59,
	 0,60, 0,61, 0,62, 0,63};
const uint8_t Decimal_Table_CoeffToken1[COEFF_TOKEN_TABLE_SIZE]{
 1,1, 0,0, 0,0, 0,0,
 3,7, 0,1, 0,0, 0,0,
 3,4, 3,6, 2,1, 0,0,
 4,3, 5,3, 5,2, 3,5,
 4,2, 6,3, 6,2, 7,0,
 0,0, 0,0, 0,0, 0,0,
 0,0, 0,0, 0,0, 0,0,
 0,0, 0,0, 0,0, 0,0,
 0,0, 0,0, 0,0, 0,0,
 0,0, 0,0, 0,0, 0,0,
 0,0, 0,0, 0,0, 0,0,
 0,0, 0,0, 0,0, 0,0,
 0,0, 0,0, 0,0, 0,0,
 0,0, 0,0, 0,0, 0,0,
 0,0, 0,0, 0,0, 0,0,
 0,0, 0,0, 0,0, 0,0,
 0,0, 0,0, 0,0, 0,0};
const uint8_t Decimal_TableRunBefore[RUN_BEFORE_TABLE_SIZE]{
	 0,1, 0,1, 0,3, 0,3, 0,3, 0,3, 0,7, 
	 1,0, 1,1, 0,2, 0,2, 0,2, 3,0, 0,6, 
	 0,0, 2,0, 1,1, 1,1, 1,3, 2,1, 0,5,
	 0,0, 0,0, 2,0, 2,1, 1,2, 1,3, 0,4,
	 0,0, 0,0, 0,0, 3,0, 2,1, 1,2, 1,3, 
	 0,0, 0,0, 0,0, 0,0, 3,0, 0,5, 1,2, 
	 0,0, 0,0, 0,0, 0,0, 0,0, 0,4, 2,1,
	 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 3,1,
	 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 4,1, 
	 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 5,1, 
	 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 6,1, 
	 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 7,1,
	 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 8,1,
	 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 9,1, 
	 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 10,1};
const uint8_t Decimal_TotalZeros[TOTAL_ZEROS_TABLE_SIZE]{
	0,1, 0,3, 1,5, 3,3, 1,5, 5,1, 5,1, 5,1, 5,1, 4,1, 4,0, 4,0, 3,0, 2,0, 1,0,
	1,3, 0,6, 0,7, 0,7, 1,4, 4,1, 4,1, 3,1, 6,0, 5,0, 3,1, 3,1, 2,1, 1,1, 0,1,
	1,2, 0,5, 0,6, 1,5, 2,3, 0,7, 0,5, 4,1, 3,1, 2,1, 2,1, 1,1, 0,1, 0,1, 0,0,
	2,3, 0,4, 0,5, 1,4, 0,7, 0,6, 0,4, 1,3, 0,3, 0,3, 1,2, 0,1, 1,1, 0,0, 0,0,
	2,3, 1,3, 1,4, 0,6, 0,6, 0,5, 1,3, 0,3, 0,2, 0,2, 0,1, 2,1, 0,0, 0,0, 0,0,
	3,3, 1,5, 2,3, 0,5, 0,5, 0,4, 0,3, 0,2, 2,1, 1,1, 1,3, 0,0, 0,0, 0,0, 0,0,
	3,2, 1,4, 0,4, 0,4, 0,4, 1,3, 0,2, 0,2, 0,1, 3,1, 0,0, 0,0, 0,0, 0,0, 0,0,
	4,3, 2,3, 1,3, 2,3, 1,3, 1,2, 3,1, 2,1, 4,1, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 
	4,2, 2,2, 2,2, 1,3, 2,2, 3,1, 2,1, 6,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 
	5,3, 3,3, 3,3, 2,2, 4,1, 2,1, 6,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 
	5,2, 3,2, 3,2, 3,2, 3,1, 6,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
	6,3, 4,3, 5,1, 4,1, 5,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
	6,2, 4,2, 4,1, 5,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
 	7,3, 5,1, 6,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
  	7,2, 6,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 
  	8,1, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0};
/******arithmetic coding******/
template <class KeyType>
class Symbol{
	public:
		KeyType key;
		double val;
		double l_bound;
		double r_bound;
		Symbol(double val_, double l_bound_, double r_bound_):val(val_), l_bound(l_bound_), r_bound(r_bound_){};
};

template <typename KeyType>
bool SortByValue(const Symbol <KeyType> &a, const Symbol <KeyType> &b);
template <typename KeyType>
void DefineBoundary(std::vector<Symbol <KeyType> > & v);
template <typename KeyType>
std::vector <Symbol<KeyType> > MeasureProbability(KeyType arr[], int size);
template <typename KeyType>
double ArithmCoder(KeyType arr[], int size);
/******		CABAC		*******/
inline uint32_t PowOfTwo(int exp);
std::string DecToBin(uint32_t value, bool ZeroNull);
uint32_t BinToDec(std::string s);
std::string Binarization_Unary(uint32_t value);
std::string Binarization_TrUnary(uint32_t value, uint32_t cMax);
std::string Binarization_ExpGolomb(uint32_t value, uint32_t k);
uint32_t Debinarization_Unary(std::string s);
uint32_t Debinarization_ExpGolomb(std::string s);
std::string CreateBitString(uint8_t nulls, uint8_t number);
/******		CAVLC		******/

int* ZigZagCoeffs(void);
int* ReorderingMacroBlock(int *zz_coefs, int **matrix);
void GetValuesToEncode(uint8_t &TotalCoeff, uint8_t &TrailingOnes, uint8_t &TotalZeros, std::string &Sign, int arr[]);

//*******encode**********//
inline std::string Encode_GetRunBeforeFromTbl(uint8_t runBefore, uint8_t zerosLeft);
inline std::string Encode_GetCoeffTokenFromTbl(uint8_t TrailingOnes, uint8_t TotalCoeff);
inline std::string Encode_GetTotalZerosFromTbl(uint8_t TotalZeros, uint8_t TotalCoeff);
std::string Encode_CalculateRunBefore(int TotalZeros, int TotalCoeff, int arr[]);
std::string CreateLevelPrefix(int &value, int TrailingOnes, int SuffixLength);
inline void SuffixLengthLimit(int Amplitude, int &SuffixLength);
std::string Encode_GetLevel(int TrailingOnes, int TotalCoeff, int TotalZeros, int arr[]);
std::string Encode_CAVLC(int arr[]);

//********decode******//
void GetNullsAndNumber(std::string s, uint8_t& nulls, uint8_t& number);
void Decode_TotalCoeff_TrailingOnes(std::string CoeffToken, uint8_t& TotalCoeff, uint8_t &TrailingOnes);
int* Decode_Tl_Signs(std::string Sign);
uint8_t Decode_TotalZeros(std::string TotalZeros, uint8_t TotalCoeff);
uint8_t Decode_RunBefore(std::string runBefore, uint8_t &TotalZeros);
int Decode_Levels(std::string level);
int *Decode_CAVLC(std::string s);

//test
int test_encode_decode_error(int arr[], int *decoded);

#endif