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
		else if (check == OVERFLOW)
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
			return OVERFLOW;
		num = num * 10 + (arg[i] - 0);
    }
    return 0;
}

void PmergeMe::vectorSort(std::vector<unsigned int> &vec) {
	int size = vec.size();
	int half = size / 2;
	for(int i = 0; i < half; i++) {
		if(vec[i] > vec[half + i])
			std::swap(vec[i],vec[half + i]);
	}
					std::cout << "debug0: ";
			for (size_t i = 0; i < vec.size(); ++i) {
			    std::cout << vec[i] << " ";
			}
	if(half != 1) {
		std::vector<unsigned int> next(vec.begin(), vec.begin() + half);
		vectorSort(next);
		std::copy(next.begin(), next.end(), vec.begin());
	}
				std::cout << "debug1: ";
			for (size_t i = 0; i < vec.size(); ++i) {
			    std::cout << vec[i] << " ";
			}
	// if(vec.size() == 2) {
	// 	if (vec[0] > vec[1]) std::swap(vec[0], vec[1]);
	// 	return;
	// }
	int i = 1;
	int k_pre = 1;
	bool finish = false;
	while(finish == false) {
		// std::cout << "size = " << vec.size() << std::endl;
		int k = (power(2, i + 1) + power(-1, i)) / 3;
		int sorted = power(2, i) - 1;
		if(k + sorted > size) {
			finish = true;
			k = vec.size();
			std::cout << "sorted before: " << sorted << std::endl;
			sorted = half + k_pre;
			std::cout << "sorted after: " << sorted << std::endl;
		}
		for(int j = k; j > k_pre; j--) {
			unsigned int element = vec[j - 1];
			vec.erase(vec.begin() + sorted + j  - 1);
			std::cout << "j = " << j << ", sorted = " << sorted <<", k_pre = " << k_pre << std::endl;
			insertVectorElement(vec, element, 0 ,sorted - 1);
			sorted++;
			std::cout << "debug3: ";
			for (size_t i = 0; i < vec.size(); ++i) {
			    std::cout << vec[i] << " ";
			}
			std::cout << std::endl;
			std::cout << std::endl;
		}
		i++;
		k_pre = k;
	}
	std::cout << "fin" << std::endl;
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
	std::cout << "el =" << element << ", mid =" << vec[mid] << std:: endl;
    if (element < vec[mid]) {
        insertVectorElement(vec, element, left, mid);
    } else {
        insertVectorElement(vec, element, mid + 1, right);
    }
}