#pragma once
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>

class BitcoinExchange
{
private:
    std::map <std::string, std::string> _input;
    std::map <std::string, std::string> _data;
	BitcoinExchange( void );
public:
	BitcoinExchange(std::string file_name);
	BitcoinExchange(const BitcoinExchange &origin);
	virtual ~BitcoinExchange();
	BitcoinExchange& operator = (const BitcoinExchange &origin);
    void setInput(std::string file_name);
    void setData(std::string path_to_csv);
    void putExchange();
};