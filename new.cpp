#include "ArCod.hpp"
#include "DC.hpp"

int main()
{

	// testing Encode_CAVLC;
	int arr1[16] = {0,3,0,1,-1,-1,0,1,0, 0, 0, 0, 0, 0, 0, 0};
	int arr2[16] = {-2, 4, 3, -3, 0, 0, -1,0, 0, 0, 0, 0, 0, 0, 0, 0};
	int arr3[16] = {0,0,0,1,0,1,0,0,0, -1, 0, 0, 0, 0, 0, 0};
	int error_counter = 0;
	int *decoded;
	std::string s = "";

	s = Encode_CAVLC(arr1);
	decoded = Decode_CAVLC(s);
	std::cout << "error_counter1: "<< test_encode_decode_error(arr1, decoded) << std::endl;
	s = Encode_CAVLC(arr2);
	decoded = Decode_CAVLC(s);
	std::cout << "error_counter2: "<< test_encode_decode_error(arr2, decoded) << std::endl;
	s = Encode_CAVLC(arr3);
	decoded = Decode_CAVLC(s);
	std::cout << "error_counter3: "<< test_encode_decode_error(arr3, decoded) << std::endl;
	
	return 0;
}
