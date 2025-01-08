#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(const char *path_to_csv) {
    setData(path_to_csv);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &origin) {
	*this = origin;
}

BitcoinExchange::~BitcoinExchange() {
}

BitcoinExchange& BitcoinExchange::operator= (const BitcoinExchange &origin){
	if(this == &origin)
		return *this;
	_data = origin.getData();
	return *this;
}

void BitcoinExchange::setData(const char * path_to_csv) {
    std::ifstream file(path_to_csv);
     if (file.is_open()) {
    std::string line;
    std::string key;
    std::string value;
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::stringstream s(line);
        std::getline(s,key,',');
        std::getline(s,value);
        _data[key] = std::strtod(value.c_str(),NULL);
    }
        file.close();
    } else {
        std::cerr << "Error: could not open file." << std::endl;
    }
}

std::map <std::string, double> BitcoinExchange::getData() const {
    return _data;
}

void BitcoinExchange::Exchange(char * file_name) {
    std::fstream infile(file_name);
    std::string line;
    std::string value;
    std::string date;
    double rate;
     if (infile.is_open()) {
        getline(infile, line);
        while (getline(infile, line)) {
            std::stringstream s(line);
            if(getline(s, date, '|')) {
                if(!checkDate(date)) {
                    std::cerr << "Error: bad input => " << date << std::endl;
                    continue;
                }
                if(getline(s, value)){
                    if(!checkValue(value)) {
                        continue;
                    }
                    rate = getRate(date);
                    if(rate == -1) {
                        std::cerr << "Error: The database does not contain a valid date for the given input." << std::endl;
                        continue;
                    }
                    std::cout << date << "=>" << value << " = ";
                    std::cout <<  rate * std::stod(value,NULL) << std::endl;
                } else {
                    std::cerr << "Error: Invalid value format." << std::endl;
                    continue;
                }
            }
        }
        infile.close();
    } else {
        std::cerr << "Error: could not open file." << std::endl;
    }
}

double BitcoinExchange::getRate(std::string date)
{
    date.pop_back();
    std::map<std::string, double>::iterator it = _data.find(date);
    if(it == _data.end()) {
        _data[date] = 0;
        it =_data.find(date);
        if(it == _data.begin()) {
            _data.erase(date);
            return (-1);
        }
        it--;
        _data.erase(date);
    }
    return (it->second);

}

bool BitcoinExchange::checkDate(std::string date) {
    std::string year, month, day;
    std::stringstream s(date);
    if(!std::getline(s,year,'-'))
        return false;
    if(!std::getline(s,month,'-'))
        return false;
    if(!std::getline(s,day,'-'))
        return false;
    if(!checkYear(year) || !checkDay(month,day))
        return false;
    return true;
}

bool BitcoinExchange::checkYear(std::string year) {
    if(year.length() != 4 || !checkNum(year))
        return false;
    int num = std::atoi(year.c_str());
    if(num < 2009 || num > 2025)
        return false;
    return true;
}

bool BitcoinExchange::checkDay(std::string month,std::string day) {
    if(month.length() != 2 || !checkNum(month))
        return false;
    if(day.length() != 3 || day[2] != ' ')
        return false;
    if(day[1] < '0' || day[1] > '9')
        return false;
    int month_num = std::atoi(month.c_str());
    int day_num = std::atoi(day.c_str());
    if(month_num < 1 || month_num > 12)
        return false;
    if(day_num < 1 || month_num > 31)
        return false;
    if((month_num == 2 || month_num == 4 || month_num == 6 || month_num == 9 || month_num == 11) && day_num == 31)
        return false;
    if(month_num == 2 && (day_num == 30 || day_num == 29))
        return false;
    return true;
}

bool BitcoinExchange::checkValue(std::string value) {
    if(!checkDoubleNum(value)) {
        std::cerr << "Error: The input is not a valid numeric value." << std::endl;
        return false;
    }
    double value_num = std::stod(value);
    if (value_num < 1) {
        std::cerr << "Error: not a positive number." << std::endl;
        return false;
    } else if (value_num > 1000) {
        std::cerr << "Error: too large a number." << std::endl;
        return false;
    }
    return true;
}

bool BitcoinExchange::checkNum(std::string num) {
    for (size_t i = 0; i < num.length(); i++) {
        if(num[i] < '0' || num[i] > '9')
            return false;
    }
    return true;
}

bool BitcoinExchange::checkDoubleNum(std::string num) {
    int dot_flg = 0;
    if (num[0] != ' ')
        return false;
    for (size_t i = (num[1] == '-') ? 2 : 1; i < num.length(); i++) {
        if (num[i] == '.') {
            if(dot_flg == 0)
                dot_flg = 1;
            else
                return false;
        } else if(num[i] < '0' || num[i] > '9') {
            return false;
        }
    }
    return true;
}
