#include "BitcoinExchange.hpp"

int main(int argc, char **argv) {
	if(argc !=  2) {
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}
	BitcoinExchange exc(PATH_TO_CSV);
	exc.Exchange(argv[1]);
	return 0;
}