#include "PmergeMe.hpp"

int main(int argc, char **argv) {
	if(argc <  2) {
		std::cerr << "Incorrect number of arguments." << std::endl;
		return 1;
	}
	try {
		PmergeMe pm(argc,argv);
		pm.diplay();
	} catch (std::runtime_error &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0; 
}