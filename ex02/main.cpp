#include "PmergeMe.hpp"

int main(int argc, char **argv) {
	if(argc <  2) {
		std::cerr << "Incorrect number of arguments." << std::endl;
		return 1;
	}
	PmergeMe pm(argc,argv);
	pm.diplay();
	return 0; 
}