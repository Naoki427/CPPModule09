#include "RPN.hpp"

RPN::RPN() {
	
}

RPN::RPN(const RPN &origin) {
	*this = origin;
}

RPN::~RPN() {
}

RPN& RPN::operator= (const RPN &origin){
	if(this == &origin)
		return *this;
	
	return *this;
}

void RPN::Calculate(std::string input){
	if(input.empty())
		throw std::runtime_error("Input cannot be an empty line.");
	for (std::string::iterator it = input.begin(); it != input.end(); it++) {
		if (std::isspace(*it))
			continue ;
		if (std::isdigit(*it))
			_stack.push((*it) - '0');
		else {
			if (*it != '+' && *it != '-' && *it != '/' && *it != '*')
				throw std::runtime_error("Error: Input contains unexpected characters.");
			if(_stack.size() != 2)
				throw std::runtime_error("Error: A syntax error has occurred.");
			if(*it == '+') {
				if(this->add())
					throw std::runtime_error("Error: Integer overflow occurred.");
			}
			if(*it == '-') {
				if(this->subtract())
					throw std::runtime_error("Error: Integer overflow occurred.");
			}
			if(*it == '/') {
				if(this->mod())
					throw std::runtime_error("Error: Division by zero is not allowed.");
			}
			if(*it == '*') {
				if(this->multiply())
					throw std::runtime_error("Error: Integer overflow occurred.");
			}
		}
	}
	std::cout << _stack.top() << std::endl;
	_stack.pop();
}

int RPN::add(){
	int first = _stack.top();
	_stack.pop();
	int second = _stack.top();
	_stack.pop();
	if(INT_MAX - second < first)
		return 1;
	int result = first + second;
	_stack.push(result);
	return 0;
}

int RPN::subtract(){
	int first = _stack.top();
	_stack.pop();
	int second = _stack.top();
	_stack.pop();
	if(INT_MIN + first > second)
		return 1;
	int result = second - first;
	_stack.push(result);
	return 0;
}

int RPN::mod(){
	int first = _stack.top();
	_stack.pop();
	int second = _stack.top();
	_stack.pop();
	if(first == 0)
		return 1;
	int result = second / first;
	_stack.push(result);
	return 0;
}

int RPN::multiply(){
	int first = _stack.top();
	_stack.pop();
	int second = _stack.top();
	_stack.pop();
	if(first == 0) {
		_stack.push(0);
		return 0;
	}
	if(INT_MAX / first < second || INT_MIN / first > second)
		return 1;
	int result = first * second;
	_stack.push(result);
	return 0;
}
