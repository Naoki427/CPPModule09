#include "PmergeMe.hpp"

int main(int argc, char **argv) {
	if(argc <  2) {
		std::cerr << "Incorrect number of arguments." << std::endl;
		return 1;
	}
	PmergeMe pm(argc,argv);
	std::cout << "Before: ";
	for (size_t i = 0; i < pm._vector.size(); ++i) {
        std::cout << pm._vector[i] << " ";
    }
	std::cout << std::endl;
	pm.vectorSort(pm._vector);
	std::cout << "After: ";
	for (size_t i = 0; i < pm._vector.size(); ++i) {
        std::cout << pm._vector[i] << " ";
    }
	std::cout << std::endl;
	return 0; 
}