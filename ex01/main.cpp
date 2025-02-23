#include "RPN.hpp"

int main(int argc, char **argv) {
	if(argc !=  2) {
		std::cerr << "Incorrect number of arguments." << std::endl;
		return 1;
	}
	RPN rpn;
	try {
		rpn.Calculate(argv[1]);
	} catch (std::runtime_error &e) {
		std::cerr << e.what() << std::endl;
	}
	
	return 0; 
}