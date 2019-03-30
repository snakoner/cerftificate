#include "ArCod.hpp"


template <typename KeyType>
bool SortByValue(const Symbol <KeyType> &a, const Symbol <KeyType> &b){
       return a.val > b.val;}

template <typename KeyType>
void DefineBoundary(std::vector<Symbol <KeyType> > & v){
	double l = 0;
	typename std::vector <Symbol<KeyType> > ::iterator it;
	for(it=v.begin(); it!=v.end(); ++it){
		it->l_bound = l;
		it->r_bound = l + it->val;
		l = it->r_bound;
	}}

template <typename KeyType>
std::vector <Symbol<KeyType> > MeasureProbability(KeyType arr[], int size){
	bool in_vec;
	std::vector <Symbol<KeyType> > v;
	typename std::vector <Symbol<KeyType> >::iterator it;
	Symbol <KeyType> symbol(.0, .0, .0);
	//empty list with keys
	for(int i=0; i<size; i++){
		symbol.key = arr[i];
		in_vec = false;
		for(it = v.begin(); it!=v.end(); it++)
			if (it->key == arr[i])
				in_vec = true;
		if (!in_vec)
			v.push_back(symbol);
		}
	//measuring probabilities
	for(it = v.begin(); it!=v.end(); it++)
		for(int i=0; i<size; i++)
			if (it->key == arr[i])
				it->val += 1.0/size;
	std::sort(v.begin(), v.end(), SortByValue<KeyType>);
	return v;}

template <typename KeyType>
double ArithmCoder(KeyType arr[], int size){
	//initialization
	std::vector <Symbol<KeyType> > v = MeasureProbability(arr, size);	
	typename std::vector <Symbol<KeyType> >::iterator it;
	KeyType current_symb;
	// for(it=v.begin(); it!=v.end(); it++)
	//			std::cout << it->key << "\t" << it->val << "\t" << it->l_bound << "\t" << it->r_bound << std::endl;
	double left = .0;
	double right = 1.0;
	double new_left, new_right;
	//main code
	DefineBoundary(v);
	for(int i=0; i<size; i++){
		current_symb = arr[i];
		for(it=v.begin(); it!=v.end(); it++)
			if(it->key == arr[i]){
				new_left = left + (right - left)*(it->l_bound);
				new_right = left + (right - left)*(it->r_bound);
				left = new_left;
				right = new_right;
			}
	}
	return (left + right)/2.0;}

/******		CABAC		*******/
inline uint32_t PowOfTwo(int exp){
	int res = 1;
	while(exp>0){
		res *= 2;
		exp--;}
	return res;}
std::string DecToBin(uint32_t value, bool ZeroNull){
	std::string s = "";
	int tmp;
	if (value == 0 && ZeroNull)
		return s;
	while((tmp = value/2)>0){
		s+= (value%2)?"1":"0";
		value = tmp;}
	s += (value)? "1" : "0";
	std::reverse(s.begin(), s.end());
	return s;}
uint32_t BinToDec(std::string s){
	std::string::iterator it = s.end()-1;
	uint32_t res = 0;
	uint32_t cnt = 0;
	for(it; it >= s.begin(); it--){
		if (*it == '1')
			res += PowOfTwo(cnt);
		cnt++;
	}
	return res;
	}
std::string Binarization_Unary(uint32_t value){
	std::string s = "";
	for(int i=0; i<value; i++)
		s += "1";
	return s+="0";}
std::string Binarization_TrUnary(uint32_t value, uint32_t cMax){
	if (value < cMax)
		return Binarization_Unary(value);
	else{
		std::string s = "";
		for(int i=0; i<value; i++)
			s+="1";
		return s;}}
std::string Binarization_ExpGolomb(uint32_t value, uint32_t k){
	uint8_t OnesNumber = 0;
	std::string s = DecToBin(value, 0);
	std::string res = "";
	if (k) 
		s.erase(s.end()-k, s.end());
	s = DecToBin(BinToDec(s)+1,0);
	for(int i=0; i<s.size()-1; i++)
		res += "0";
	res += s;
	return res;}
uint32_t Debinarization_Unary(std::string s){
	size_t size = s.size();
	return (s[size-1]=='0')?(size-1):(size);}
uint32_t Debinarization_ExpGolomb(std::string s){
	s.erase(0, s.find('1'));
	return BinToDec(s)-1;}
std::string CreateBitString(uint8_t nulls, uint8_t number){
	std::string s = "";
	for(int i=0; i<nulls; i++)
		s += "0";
	s += DecToBin(number,1);
	return s;
}
/******		CAVLC		******/

//preencode
int* ZigZagCoeffs(void){
	/* this function creates the zig zag traversal order */
	int *res = (int *)malloc(MATRIX_REORDERING_SIZE*sizeof(int));
	int row, col;
	int cnt = 0;
	row = 0;
	col = 0;
	for(int i=0; i<MATRIX_REORDERING_SIZE/2; i++){
		if(((row == 0) || (row == N-1)) && (col%2==0)){
			res[cnt++] = row;
			res[cnt++] = col;
			col++;}
		else if((row == 0) && (col%2)){ //  /
			while(col>0){
			res[cnt++] = row;
			res[cnt++] = col;
				row++;
				col--;}}
		else if((row%2) && (row!=N-1) && (col==0)){ // |
			res[cnt++] = row;
			res[cnt++] = col;
					row++;}
		else if((row%2==0) && (col==0)){	// /
			while(row>0){
			res[cnt++] = row;
			res[cnt++] = col;
				row--;
				col++;}}
		else if((row == N-1) && (col%2) && (col!=N-1)){
			while(col != N-1){
			res[cnt++] = row;
			res[cnt++] = col;
				col++;
				row --;}}
		else if((row%2==1) && (row!=N-1) && (col==N-1)){
			res[cnt++] = row;
			res[cnt++] = col;
					row++;}
		else if((row%2==0) && (col==N-1)){
			while(row!=N-1){
			res[cnt++] = row;
			res[cnt++] = col;
				row++;
				col--;}}
		else if ((row == N-1) && (col == N-1)){	
			res[cnt++] = row;
			res[cnt++] = col;
			return res;}
		}}
int* ReorderingMacroBlock(int *zz_coefs, int **matrix){
	int *arr = (int *)malloc(MATRIX_REORDERING_SIZE*sizeof(int)/2);
	int cnt = 0;
	for(int i=0; i<MATRIX_REORDERING_SIZE; i+=2){
		arr[cnt++] = matrix[zz_coefs[i]][zz_coefs[i+1]];	}
	return arr;}
void GetValuesToEncode(uint8_t &TotalCoeff, uint8_t &TrailingOnes, uint8_t &TotalZeros, std::string &Sign, int arr[]){
	/* this function calculate TotalCoeff, TrailingOnes, TotalZeros and Trailing One signs (create neccessary string)
		by changing variables with references from arr */
	int Tl_counter = 0;
	int tmp_TotalZeros = 0;
	TotalCoeff = 0;
	TrailingOnes = 0;
	TotalZeros = 0;
	//for(int i=0; i<MB_SIZE*MB_SIZE; i++)
		//std::cout << arr[i] << "\t" << std::endl;

	for(int i=0; i<MB_SIZE*MB_SIZE; ++i){
		//std::cout << "elen: "<<arr[i] << std::endl;
		if(arr[i]){
			TotalZeros = 0;
			TotalCoeff++;
			if((arr[i] == 1)){
					TrailingOnes++;
					Sign += "0";}
			else if((arr[i] == -1)){
					TrailingOnes++;
					Sign += "1";}
				}
		else{
			TotalZeros++;}
		}
	if (Sign.length()>3){
		TrailingOnes = 3;
		Sign.erase(Sign.begin(), Sign.begin() + Sign.length()-3);
	}
	std::reverse(Sign.begin(), Sign.end());
	TotalZeros = MB_SIZE*MB_SIZE - TotalZeros - TotalCoeff;}
//*******encode**********//
inline std::string Encode_GetRunBeforeFromTbl(uint8_t runBefore, uint8_t zerosLeft){
		uint8_t nulls = (zerosLeft>6)? Decimal_TableRunBefore[12 + runBefore*ZEROS_LEFT_LIMITS]:Decimal_TableRunBefore[2*zerosLeft - 2 + runBefore*ZEROS_LEFT_LIMITS];
		uint8_t number = (zerosLeft>6)? Decimal_TableRunBefore[12 + runBefore*ZEROS_LEFT_LIMITS + 1]:Decimal_TableRunBefore[2*zerosLeft - 1 + runBefore*ZEROS_LEFT_LIMITS];
		return CreateBitString(nulls, number);}
inline std::string Encode_GetCoeffTokenFromTbl(uint8_t TrailingOnes, uint8_t TotalCoeff){
		uint8_t nulls = Decimal_Table_CoeffToken02[TotalCoeff*2*TRAILING_ONES_LIMITS + 2*TrailingOnes];
		uint8_t number = Decimal_Table_CoeffToken02[TotalCoeff*2*TRAILING_ONES_LIMITS + 2*TrailingOnes + 1];
		return CreateBitString(nulls, number);}
inline std::string Encode_GetTotalZerosFromTbl(uint8_t TotalZeros, uint8_t TotalCoeff){
		uint8_t nulls = Decimal_TotalZeros[TotalZeros*2*TOTAL_ZEROS_LIMITS + 2*(TotalCoeff - 1)];
		uint8_t number = Decimal_TotalZeros[TotalZeros*2*TOTAL_ZEROS_LIMITS + 2*(TotalCoeff - 1) + 1];
		return CreateBitString(nulls, number);}
std::string Encode_CalculateRunBefore(int TotalZeros, int TotalCoeff, int arr[]){
	/* this functions calculates run before zeros and encode them*/
	std::string encoded_string = "";
	int tmp_cnt;
	int run_before = 0;
	for(int i=TotalCoeff + TotalZeros - 1; i>=0; --i){
		if (arr[i]){
			TotalCoeff--;
			run_before = 0;
			tmp_cnt = i - 1;
			if (arr[tmp_cnt])
				run_before = 0;
			else
			while(arr[tmp_cnt]==0){
 				tmp_cnt--;
				run_before++;}
		encoded_string += Encode_GetRunBeforeFromTbl(run_before, TotalZeros)+"_";
	}
		else
			TotalZeros--;
		if (TotalZeros == 0 || TotalCoeff == 1) break; }	// dont code
	return encoded_string;
	}
std::string CreateLevelPrefix(int &value, int TrailingOnes, int SuffixLength){
	std::string s = "";
	if (TrailingOnes < 3)
		value += (value < 0)?(1):(-1);
	int level_code = (value>0)?((value << 1) - 2):(-((value << 1) + 1));
	int level_prefix = level_code/(1 << SuffixLength);
	std::cout << "lc: " << level_code << std::endl;
	std::cout << "lp: " << level_prefix << std::endl;
	for(int i=0; i<level_prefix; i++)
			s += "0";
	s += "1";
	for(int i=0; i<SuffixLength; i++)
		s += (value > 0)?("0"):("1");
	return s;
}
inline void SuffixLengthLimit(int Amplitude, int &SuffixLength){
	Amplitude = (Amplitude<0)?(-Amplitude):(Amplitude);
	if ((SuffixLength == 0) || ((SuffixLength == 1) && (Amplitude >= 3)) 
		|| ((SuffixLength == 2) && (Amplitude >= 6)) || ((SuffixLength == 3) && (Amplitude >= 12)) 
		|| ((SuffixLength == 4) && (Amplitude >= 24)) || ((SuffixLength == 5) && (Amplitude >= 48)))
		SuffixLength++;
	}

/*std::string Encode_GetLevel(int TrailingOnes, int TotalCoeff, int TotalZeros, int arr[]){
	int *tmp_arr = (int *)malloc((TotalCoeff - TrailingOnes)*sizeof(int));
	int SuffixLength = 0;
	int tl_cnt = 0;
	int cnt = 0;
	std::string s = " ";
	if(TotalCoeff > 10 && TotalZeros < 3)
		SuffixLength = 1;
	for(int i=TotalZeros + TotalCoeff-1; i>=0; i--){
		if ((arr[i] == 1 || arr[i] == -1) && (tl_cnt < TrailingOnes)){
			tl_cnt++;
			continue;
		}
		if(tl_cnt == TrailingOnes){
			if (arr[i]){
				tmp_arr[cnt++] =arr[i];
			}
		}
	}
	for(int i= 0; i < TotalCoeff - TrailingOnes ; i++){
		int value = tmp_arr[i];
		std::cout << "value: " << value <<std::endl;
		s += CreateLevelPrefix(tmp_arr[i], TrailingOnes, SuffixLength);

		SuffixLengthLimit(tmp_arr[i], SuffixLength);
		std::cout << "value: " << tmp_arr[i] <<std::endl;

		std::cout << s << std::endl;
		s.clear();
	}
	return s;}*/
std::string Encode_GetLevel(int TrailingOnes, int TotalCoeff, int TotalZeros, int arr[]){
	int *tmp_arr = (int *)malloc((TotalCoeff - TrailingOnes)*sizeof(int));
	int SuffixLength = 0;
	int tl_cnt = 0;
	int cnt = 0;
	std::string s = "";
	if(TotalCoeff > 10 && TotalZeros < 3)
		SuffixLength = 1;
	for(int i=TotalZeros + TotalCoeff-1; i>=0; i--){
		if ((arr[i] == 1 || arr[i] == -1) && (tl_cnt < TrailingOnes)){
			tl_cnt++;
			continue;
		}
		if(tl_cnt == TrailingOnes){
			if (arr[i]){
				tmp_arr[cnt++] =arr[i];}
		}
	}
	for(int i= 0; i < TotalCoeff - TrailingOnes; i++){
		int value = tmp_arr[i];
		s += (value>0)?("0"):("1");
		s += DecToBin((value>0)?(value):(-value),0);
		if(i!= TotalCoeff - TrailingOnes -1) s += "_";
	}
	return s;
}

std::string Encode_CAVLC(int arr[]){
	std::string s = "";
	uint8_t TotalCoeff;
	uint8_t TrailingOnes;
	uint8_t TotalZeros;
	std::string Sign;
	GetValuesToEncode(TotalCoeff, TrailingOnes, TotalZeros, Sign, arr);
	s += Encode_GetCoeffTokenFromTbl(TrailingOnes, TotalCoeff) + "_";
	s += Sign + "_";
	if ((TotalCoeff - TrailingOnes) > 0)
	s += Encode_GetLevel(TrailingOnes, TotalCoeff, TotalZeros, arr) + "_";
	s += Encode_GetTotalZerosFromTbl(TotalZeros, TotalCoeff)+"_";
	s += Encode_CalculateRunBefore(TotalZeros, TotalCoeff, arr);
	s.erase(s.length()-1, s.length());
	return s;}

//********decode******//

void GetNullsAndNumber(std::string s, uint8_t& nulls, uint8_t& number){
	nulls = 0;
	number = 0;
	for(int i=0; i<s.length(); i++){
		if (s[i] == '0')
			nulls++;
		else if (s[i] == '1'){
			number = BinToDec(s.erase(0,i));
			break;
		}
	}}
void Decode_TotalCoeff_TrailingOnes(std::string CoeffToken, uint8_t& TotalCoeff, uint8_t &TrailingOnes){
	uint8_t nulls;
	uint8_t number;
	GetNullsAndNumber(CoeffToken, nulls, number);
	for(int i=0; i<COEFF_TOKEN_TABLE_SIZE; i+=2)
		if ((Decimal_Table_CoeffToken02[i] == nulls) && (Decimal_Table_CoeffToken02[i+1] == number)){
			TrailingOnes = (i/2)%TRAILING_ONES_LIMITS;
			TotalCoeff = (i/2)/TRAILING_ONES_LIMITS;
			break;}}
int* Decode_Tl_Signs(std::string Sign){
	size_t size = Sign.length();
	std::string null = "0";
	int *result = (int *)malloc(size*sizeof(int));
	bool b = Sign[0] == '0';
	for(int i=0; i<size; i++){
		result[i] = (Sign[i] == '1')?(-1):(1);
	}
	return result;}
uint8_t Decode_TotalZeros(std::string TotalZeros, uint8_t TotalCoeff){
	uint8_t nulls;
	uint8_t number;
	TotalCoeff--;
	GetNullsAndNumber(TotalZeros, nulls, number);
	for(int i=0; i<TOTAL_ZEROS_LIMITS; i++){
		if ((Decimal_TotalZeros[2*TOTAL_ZEROS_LIMITS*i + 2*TotalCoeff] == nulls) && (Decimal_TotalZeros[2*TOTAL_ZEROS_LIMITS*i + 2*TotalCoeff + 1] == number))
			{
				return i;
			}
		}
	}
uint8_t Decode_RunBefore(std::string runBefore, uint8_t &TotalZeros){
	uint8_t nulls;
	uint8_t number;
	GetNullsAndNumber(runBefore, nulls, number);
	for(int i=0; i<ZEROS_LEFT_LIMITS; i++){
		if (TotalZeros > 6){
			if((Decimal_TableRunBefore[2*i*7 + 2*6] == nulls) && (Decimal_TableRunBefore[2*i*7 + 2*6 + 1] == number)){
				TotalZeros -= i;
				return i;}
			}
			
			else{
				if ((Decimal_TableRunBefore[2*i*7 + 2*(TotalZeros-1)]  == nulls) && (Decimal_TableRunBefore[2*i*7 + 2*(TotalZeros-1) + 1] == number)){
					TotalZeros -= i;
					return i;
				}
			}
		}
		}
int Decode_Levels(std::string level){
	int sign = (level[0]=='0')?(1):(-1);
	return sign*(BinToDec(level.erase(0, 1)));}
int** OrderingMacroBlock(int *zz_coefs, int *coeffs){
	int cnt = 0;
	int **ordered_mb = (int **)calloc(N, sizeof(int*));
	for(int i=0; i<N; i++)
		ordered_mb[i] = (int *)calloc(N, sizeof(int));
	for(int i=0; i<2*MB_SIZE*MB_SIZE; i+=2){
		ordered_mb[zz_coefs[i]][zz_coefs[i+1]] = coeffs[cnt++];
	}
	return ordered_mb;
}
int *Decode_CAVLC(std::string s){
	std::vector <std::string> cutted_bits;
	std::vector <int> res;
	std::vector <int> seq;
	std::vector <int>::iterator it;
	int *final_seq = (int *)malloc(MB_SIZE*MB_SIZE*sizeof(int));
	int *Tls;
	int pos;
	int cnt = 0;
	uint8_t TrailingOnes, TotalCoeff, TotalZeros, copy_TotalZeros;
	std::string tmp_str = "";
	while((pos=s.find("_"))!=std::string::npos){
		cutted_bits.push_back(s.substr(0, pos));
		s.erase(0, pos+1);}
	cutted_bits.push_back(s);
	Decode_TotalCoeff_TrailingOnes(cutted_bits[0], TotalCoeff, TrailingOnes);
	TotalZeros = Decode_TotalZeros(cutted_bits[TotalCoeff - TrailingOnes + 2], TotalCoeff);
	copy_TotalZeros = TotalZeros;

	if ((TotalCoeff - TrailingOnes)>0)
	{
		for(int i=1+TotalCoeff - TrailingOnes;i>=2; i--){
		res.push_back(Decode_Levels(cutted_bits[i]));
		}
	}
	Tls = Decode_Tl_Signs(cutted_bits[1]);
	for(int i=TrailingOnes-1; i>=0; i--)
		res.push_back(Tls[i]);
	int *run_before = (int *)malloc((cutted_bits.size()-(TotalCoeff - TrailingOnes + 3))*sizeof(int));
	for(int i=TotalCoeff - TrailingOnes + 3; i<cutted_bits.size(); i++){
		run_before[cnt++] = Decode_RunBefore(cutted_bits[i], TotalZeros);
	}
	cnt =0;
	for(it = res.end()-1; it>=res.begin(); it--){
		seq.push_back(*it);
		if (cnt < (cutted_bits.size()-(TotalCoeff - TrailingOnes + 3))){
		for(int i=0; i < run_before[cnt]; i++)
			seq.push_back(0);
		cnt++;
	}}
	std::reverse(seq.begin(), seq.end());
	for(int i=0; i<MB_SIZE*MB_SIZE - (TotalCoeff + copy_TotalZeros); i++)
		seq.push_back(0);
	it = seq.begin();
	seq.insert(it, TotalZeros, 0);
	for(int i=0; i<seq.size(); i++)
		final_seq[i] = seq[i];
	free(Tls);
	return final_seq;}
/****					*****/
int test_encode_decode_error(int arr[], int *decoded){
	int error_counter = 0;
	for(int i=0; i<MB_SIZE*MB_SIZE; i++){
		error_counter += (decoded[i] != arr[i]);
	}
	return error_counter;
}
