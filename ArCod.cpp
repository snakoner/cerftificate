#include <iostream>
#include <map>
#include <algorithm> 
#include <vector>

template <class KeyType>
class Symbol{
	public:
		KeyType key;
		double val;
		double l_bound;
		double r_bound;
	Symbol(double val, double l_bound, double r_bound){
		this->val = val;
		this->l_bound = l_bound;
		this->r_bound = r_bound;
	}
};
template <typename KeyType>
bool SortByValue(const Symbol <KeyType> &a, const Symbol <KeyType> &b){
       return a.val > b.val;
}
template <typename KeyType>
void DefineBoundary(std::vector<Symbol <KeyType> > & v){
	double l = 0;
	typename std::vector <Symbol<KeyType> > ::iterator it;
	for(it=v.begin(); it!=v.end(); ++it){
		it->l_bound = l;
		it->r_bound = l + it->val;
		l = it->r_bound;
	}
}
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
	return v;
}
template <typename KeyType>
double ArithmCoder(KeyType arr[], int size){
	//initialization
	std::vector <Symbol<KeyType> > v = MeasureProbability(arr, size);	
	typename std::vector <Symbol<KeyType> >::iterator it;
	KeyType current_symb;
			for(it=v.begin(); it!=v.end(); it++)
				std::cout << it->key << "\t" << it->val << "\t" << it->l_bound << "\t" << it->r_bound << std::endl;
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
	return (left + right)/2.0;
	}


//test
int main(int argc, char const *argv[])
{
	int size = 24;
	int arr[24] = {6,51,8,4,8,2,6,51,8,4,8,2,6,51,8,4,8,2,6,51,8,4,8,2};
	std::cout << ArithmCoder(arr, size);
    return 0;
}
