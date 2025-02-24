#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(int argc,char *argv[]) {
	vectorInit(argc,argv);
}

PmergeMe::PmergeMe(const PmergeMe &origin) {
	*this = origin;
}

PmergeMe::~PmergeMe() {
}

PmergeMe& PmergeMe::operator= (const PmergeMe &origin){
	if(this == &origin)
		return *this;
	
	return *this;
}

void PmergeMe::vectorInit(int argc, char *argv[]) {
	for (int i = 1; i < argc; ++i) {
		int check = this->isNumber(argv[i]);
		if(check == INVALID_ARG)
			throw std::runtime_error("Error: Input contains unexpected characters.");
		else if (check == UINBT_OVERFLOW)
			throw std::runtime_error("Error: Overflow occurred.");
        _vector.push_back(std::atoi(argv[i]));
    }
}

int PmergeMe::isNumber(char *arg) {
	unsigned int num = 0;
    for (size_t i = 0; arg[i]; i++) {
        if (!std::isdigit(arg[i])) {
            return INVALID_ARG;
        }
		if (UINT_MAX - (arg[i] - 0) / 10 < num)
			return UINBT_OVERFLOW;
		num = num * 10 + (arg[i] - 0);
    }
    return 0;
}

void PmergeMe::vectorSort(std::vector<unsigned int> &vec) {
	int vec_size = vec.size();
	if(vec_size  == 1)
		return;
	int half = vec_size / 2;
	std::vector<unsigned int> big(half);
	std::vector<Data> small(vec_size - half);
	std::copy(vec.begin(), vec.begin() + half, big.begin());
	initValueV(vec.begin() + half, vec.end(), small);
	for(int i = 0; i < half; i++) {
		if(big[i] < small[i].value)
			swapBigSmallV(big[i],small[i].value);
		small[i].id = big[i];
	}
	if(vec_size % 2 == 1) {
		small[half].id = 0;
	}
	vectorSort(big);
	vec.clear();
	vec.insert(vec.end(), big.begin(), big.end());
	int first_small = getSmallIndexV(big[0],small);
	vec.insert(vec.begin(), small[first_small].value);
	small.erase(small.begin() + first_small);
	int k = 2;
	int t_pre = 1;
	bool finish = false;
	while(finish == false) {
		int t = (power(2, k + 1) + power(-1, k)) / 3;
		int sorted = power(2, k) - 1;
		int big_size = big.size();
		if (t > big_size) {
			sorted -= (t - big_size - 1);
			t = big_size;
			finish = true;
			if(vec_size % 2 == 1) {
				int no_pair = getSmallIndexV(0,small);
				insertVectorElement(vec,small[no_pair].value,0,sorted);
				sorted++;
				small.erase(small.begin() + no_pair);
			}
		}
		for (int i = t; i > t_pre; i--)
		{
			int small_i = getSmallIndexV(big[i - 1],small);
			insertVectorElement(vec,small[small_i].value,0,sorted);
			sorted++;
			small.erase(small.begin() + small_i);
		}
		t_pre = t;
		k++;
	}
}

void PmergeMe::initValueV(std::vector<unsigned int>::iterator start,std::vector<unsigned int>::iterator end, std::vector<Data>& vec) {
	for (size_t i = 0; start != end; ++start, ++i) {
		vec[i].value = *start;
	}
}

void PmergeMe::swapBigSmallV(unsigned int &big, unsigned int &small) {
	unsigned int tmp = small;
	small = big;
	big = tmp;
}

int PmergeMe::getSmallIndexV(unsigned int value, const std::vector<Data>& small) {
    for (size_t i = 0; i < small.size(); ++i) {
        if (small[i].id == value) {
            return i;
        }
    }
    return 0;
}

int PmergeMe::power(int base, int exponent) {
    int result = 1;
    for (int i = 0; i < exponent; ++i) {
        result *= base;
    }
    return result;
}

void PmergeMe::insertVectorElement(std::vector<unsigned int>& vec,unsigned  int element, int left, int right) {
    if (left >= right) {
        vec.insert(vec.begin() + left, element);
        return;
    }

    int mid = left + (right - left) / 2;
    if (element < vec[mid]) {
        insertVectorElement(vec, element, left, mid);
    } else {
        insertVectorElement(vec, element, mid + 1, right);
    }
}

//for debug
// void PmergeMe::vectorSort(std::vector<unsigned int> &vec) {
// 	int vec_size = vec.size();
// 	if(vec_size  == 1)
// 		return;
// 	int half = vec_size / 2;
// 	std::vector<unsigned int> big(half);
// 	std::vector<Data> small(vec_size - half);
// 	std::copy(vec.begin(), vec.begin() + half, big.begin());
// 	initValueV(vec.begin() + half, vec.end(), small);
// 	for(int i = 0; i < half; i++) {
// 		if(big[i] < small[i].value)
// 			swapBigSmallV(big[i],small[i].value);
// 		small[i].id = big[i];
// 	}
// 	if(vec_size % 2 == 1) {
// 		small[half].id = 0;
// 	}
// 	vectorSort(big);
// 	vec.clear();
// 	vec.insert(vec.end(), big.begin(), big.end());
// 	int first_small = getSmallIndexV(big[0],small);
// 	vec.insert(vec.begin(), small[first_small].value);
// 	small.erase(small.begin() + first_small);
// 	std::cout << "big ";
// 	for (size_t i = 0; i < big.size(); ++i) {
// 		std::cout << big[i] << " ";
// 	}
// 	std::cout << std::endl;
// 	std::cout  << "small ";
// 	for (size_t i = 0; i < small.size(); ++i) {
// 		std::cout << small[i].value << "-" << small[i].id << " ";
// 	}
// 	std::cout << std::endl;
// 	std::cout << std::endl;
// 	int k = 2;
// 	int t_pre = 1;
// 	bool finish = false;
// 	while(finish == false) {
// 		int t = (power(2, k + 1) + power(-1, k)) / 3;
// 		int sorted = power(2, k) - 1;
// 		int big_size = big.size();
// 		if (t > big_size) {
// 			sorted -= (t - big_size - 1);
// 			t = big_size;
// 			finish = true;
// 			if(vec_size % 2 == 1) {
// 				int no_pair = getSmallIndexV(0,small);
// 				insertVectorElement(vec,small[no_pair].value,0,sorted);
// 				sorted++;
// 				small.erase(small.begin() + no_pair);
// 			}
// 		}
// 		for (int i = t; i > t_pre; i--)
// 		{
// 			int small_i = getSmallIndexV(big[i - 1],small);
// 			insertVectorElement(vec,small[small_i].value,0,sorted);
// 			sorted++;
// 			small.erase(small.begin() + small_i);
// 		}
// 		t_pre = t;
// 		k++;
// 	}
// }
