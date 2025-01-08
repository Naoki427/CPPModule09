#pragma once
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <cstdlib>

#define PATH_TO_CSV "cpp_09/data.csv"

class BitcoinExchange
{
private:
    std::map <std::string, double> _data;
	BitcoinExchange( void );
public:
	BitcoinExchange(const char *path_to_csv);
	BitcoinExchange(const BitcoinExchange &origin);
	virtual ~BitcoinExchange();
	BitcoinExchange& operator = (const BitcoinExchange &origin);
    void setData(const char *path_to_csv);
	std::map <std::string, double> getData() const;
    void Exchange(char * inputfile);
	double getRate(std::string date);
	bool checkDate(std::string date);
	bool checkYear(std::string year);
	bool checkDay(std::string month,std::string day);
	bool checkValue(std::string value);
	bool checkNum(std::string num);
	bool checkDoubleNum(std::string num);
};

double ft_stod(std::string str);