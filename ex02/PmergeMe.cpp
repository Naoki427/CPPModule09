#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(int argc,char *argv[]) {
	vectorInit(argc,argv);
	dequeInit(argc,argv);
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

void PmergeMe::diplay() {
	std::cout << "Before: ";
	for (size_t i = 0; i < _vector.size(); ++i) {
        std::cout << _vector[i] << " ";
    }
	std::cout << std::endl;
	std::clock_t vec_start = std::clock();
	vectorSort(_vector);
	std::clock_t vec_end = std::clock();
	std::clock_t deq_start = std::clock();
	dequeSort(_deque);
	std::clock_t deq_end = std::clock();
		std::cout << "After: ";
	for (size_t i = 0; i < _vector.size(); ++i) {
        std::cout << _vector[i] << " ";
    }
	std::cout << std::endl;
	double vec_duration = 1000000.0 * (vec_end - vec_start) / CLOCKS_PER_SEC;
    double deq_duration = 1000000.0 * (deq_end - deq_start) / CLOCKS_PER_SEC;

    std::cout << "Time to process a range of " << _vector.size() << " elements with std::vector : "
              << vec_duration << " us" << std::endl;
    std::cout << "Time to process a range of " << _deque.size() << " elements with std::deque : "
              << deq_duration << " us" << std::endl;
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

int PmergeMe::power(int base, int exponent) {
    int result = 1;
    for (int i = 0; i < exponent; ++i) {
        result *= base;
    }
    return result;
}

void PmergeMe::swapBigSmall(unsigned int &big, unsigned int &small) {
	unsigned int tmp = small;
	small = big;
	big = tmp;
}

//vector
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
			swapBigSmall(big[i],small[i].value);
		small[i].id = big[i];
	}
	if(vec_size % 2 == 1) {
		small[half].id = 0;
	}
	vectorSort(big);
	vec.clear();
	vec.insert(vec.end(), big.begin(), big.end());
	int k = 1;
	int t_pre = 0;
	while(small.size()) {
		int t = (power(2, k + 1) + power(-1, k)) / 3;
		int big_size = big.size();
		if (t > big_size) {
			t = big_size;
			if(vec_size % 2 == 1) {
				int no_pair = getSmallIndexV(0,small);
				insertVectorElement(vec,small[no_pair].value,0,vec.size());
				small.erase(small.begin() + no_pair);
			}
		}
		for (int i = t; i > t_pre; i--)
		{
			int small_i = getSmallIndexV(big[i - 1],small);
			int left = findLeftV(vec,small[small_i].id);
			insertVectorElement(vec,small[small_i].value,0,left);
			small.erase(small.begin() + small_i);
		}
		t_pre = t;
		k++;
	}
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


void PmergeMe::initValueV(std::vector<unsigned int>::iterator start,std::vector<unsigned int>::iterator end, std::vector<Data>& vec) {
	for (size_t i = 0; start != end; ++start, ++i) {
		vec[i].value = *start;
	}
}


int PmergeMe::getSmallIndexV(unsigned int value, const std::vector<Data>& small) {
    for (size_t i = 0; i < small.size(); ++i) {
        if (small[i].id == value) {
            return i;
        }
    }
    return 0;
}

int PmergeMe::findLeftV(std::vector<unsigned int>& vec, unsigned int value) {
	int i = 0;
	for(std::vector<unsigned int>::iterator it = vec.begin(); it != vec.end(); i++,it++) {
		if(vec[i] == value)
			return i;
	}
	return 0;
}

//deque
void PmergeMe::dequeInit(int argc, char *argv[]) {
    for (int i = 1; i < argc; ++i) {
        int check = this->isNumber(argv[i]);
        if(check == INVALID_ARG)
            throw std::runtime_error("Error: Input contains unexpected characters.");
        else if (check == UINBT_OVERFLOW)
            throw std::runtime_error("Error: Overflow occurred.");
        _deque.push_back(std::atoi(argv[i]));
    }
}

void PmergeMe::dequeSort(std::deque<unsigned int> &deq) {
    int deq_size = deq.size();
    if(deq_size == 1)
        return;
    int half = deq_size / 2;
    std::deque<unsigned int> big(half);
    std::deque<Data> small(deq_size - half);
    std::copy(deq.begin(), deq.begin() + half, big.begin());
    initValueD(deq.begin() + half, deq.end(), small);
    for(int i = 0; i < half; i++) {
        if(big[i] < small[i].value)
            swapBigSmall(big[i], small[i].value);
        small[i].id = big[i];
    }
    if(deq_size % 2 == 1) {
        small[half].id = 0;
    }
    dequeSort(big);
    deq.clear();
    deq.insert(deq.end(), big.begin(), big.end());
    int k = 1;
    int t_pre = 0;
    while(small.size()) {
        int t = (power(2, k + 1) + power(-1, k)) / 3;
        int big_size = big.size();
        if (t > big_size) {
            t = big_size;
            if(deq_size % 2 == 1) {
                int no_pair = getSmallIndexD(0, small);
                insertDequeElement(deq, small[no_pair].value, 0, deq.size());
                small.erase(small.begin() + no_pair);
            }
        }
        for (int i = t; i > t_pre; i--) {
            int small_i = getSmallIndexD(big[i - 1], small);
            int left = findLeftD(deq, small[small_i].id);
            insertDequeElement(deq, small[small_i].value, 0, left);
            small.erase(small.begin() + small_i);
        }
        t_pre = t;
        k++;
    }
}

void PmergeMe::insertDequeElement(std::deque<unsigned int>& deq, unsigned int element, int left, int right) {
    if (left >= right) {
        deq.insert(deq.begin() + left, element);
        return;
    }

    int mid = left + (right - left) / 2;
    if (element < deq[mid]) {
        insertDequeElement(deq, element, left, mid);
    } else {
        insertDequeElement(deq, element, mid + 1, right);
    }
}

void PmergeMe::initValueD(std::deque<unsigned int>::iterator start, std::deque<unsigned int>::iterator end, std::deque<Data>& deq) {
    for (size_t i = 0; start != end; ++start, ++i) {
        deq[i].value = *start;
    }
}

int PmergeMe::getSmallIndexD(unsigned int value, const std::deque<Data>& small) {
    for (size_t i = 0; i < small.size(); ++i) {
        if (small[i].id == value) {
            return i;
        }
    }
    return 0;
}

int PmergeMe::findLeftD(std::deque<unsigned int>& deq, unsigned int value) {
    int i = 0;
    for(std::deque<unsigned int>::iterator it = deq.begin(); it != deq.end(); i++, it++) {
        if(deq[i] == value)
            return i;
    }
    return 0;
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
// 			swapBigSmall(big[i],small[i].value);
// 		small[i].id = big[i];
// 	}
// 	if(vec_size % 2 == 1) {
// 		small[half].id = 0;
// 	}
// 	vectorSort(big);
// 	vec.clear();
// 	vec.insert(vec.end(), big.begin(), big.end());
// 	std::cout << std::endl;
// 	std::cout  << "container ";
// 		for (size_t i = 0; i < vec.size(); ++i) {
// 			std::cout << vec[i] << " ";
// 		}
// 	std::cout << std::endl;
// 	std::cout  << "small ";
// 	for (size_t i = 0; i < small.size(); ++i) {
// 		std::cout << small[i].value << "(" << small[i].id << ") ";
// 	}
// 	std::cout << std::endl;
// 	std::cout << std::endl;
// 	int k = 1;
// 	int t_pre = 0;
// 	while(small.size()) {
// 		int t = (power(2, k + 1) + power(-1, k)) / 3;
// 		int big_size = big.size();
// 		if (t > big_size) {
// 			t = big_size;
// 			if(vec_size % 2 == 1) {
// 				int no_pair = getSmallIndexV(0,small);
// 				insertVectorElement(vec,small[no_pair].value,0,vec.size());
// 				small.erase(small.begin() + no_pair);
// 			}
// 		}
// 		for (int i = t; i > t_pre; i--)
// 		{
// 			int small_i = getSmallIndexV(big[i - 1],small);
// 			int left = findLeftV(vec,small[small_i].id);
// 			insertVectorElement(vec,small[small_i].value,0,left);
// 			small.erase(small.begin() + small_i);
// 		}
// 		std::cout << std::endl;
// 		t_pre = t;
// 		k++;
// 	}
// }
// void PmergeMe::insertVectorElement(std::vector<unsigned int>& vec,unsigned  int element, int left, int right) {
//     if (left >= right) {
//         vec.insert(vec.begin() + left, element);
//         return;
//     }

//     int mid = left + (right - left) / 2;
// 	std::cout << "compare " << element << " with " << vec[mid] << std::endl;
//     if (element < vec[mid]) {
//         insertVectorElement(vec, element, left, mid);
//     } else {
//         insertVectorElement(vec, element, mid + 1, right);
//     }
// }

