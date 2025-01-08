#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(std::string file_name) {
	
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &origin) {
	*this = origin;
}

BitcoinExchange::~BitcoinExchange() {
}

BitcoinExchange& BitcoinExchange::operator= (const BitcoinExchange &origin){
	if(this == &origin)
		return *this;
	
	return *this;
}

void BitcoinExchange::setInput(std::string file_name){
    std::fstream infile;
    std::string line;
    std::string word;
    std::string date;
     if (infile.is_open()) {
        while (getline(infile, line)) {
            std::stringstream s(line);
            if(getline(s, word, '|')) {
                date = word;
                if(getline(s, word)){
                    _input[date] = word;
                } else {
                    _input[date] = "";
                }
            }
        }
        infile.close();
    } else {
        std::cerr << "Unable to open file";
    }
}

void BitcoinExchange::setData(std::string path_to_csv) {
    
}