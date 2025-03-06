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
	_stack = origin.getStack();
	return *this;
}

std::stack<int, std::list<int> > RPN::getStack() const {
	return _stack;
}

void RPN::Calculate(std::string input){
	if(input.empty())
		throw std::runtime_error("Input cannot be an empty line.");
	char last;
	bool space = true;
	for (std::string::iterator it = input.begin(); it != input.end(); it++) {
		if (std::isspace(*it)) {
			space = true;
			continue ;
		} else {
			if(space == false)
				throw std::runtime_error("Error: The input must be space-separated.");
			space = false;
		}
		last = (*it);
		if (std::isdigit(*it))
			_stack.push((*it) - '0');
		else {
			if (*it != '+' && *it != '-' && *it != '/' && *it != '*')
				throw std::runtime_error("Error: Input contains unexpected characters.");
			else if (_stack.size() < 2)
				throw std::runtime_error("Error: A syntax error has occurred.");
			if(*it == '+')
				this->add();
			else if(*it == '-')
				this->subtract();
			else if(*it == '/')
				this->mod();
			else if(*it == '*')
				this->multiply();
		}
	}
	if(_stack.size() != 1)
		throw std::runtime_error("Error: A syntax error has occurred.");
	if(std::isdigit(last))
		throw std::runtime_error("Error: A syntax error has occurred.");
	std::cout << _stack.top() << std::endl;
	_stack.pop();
}

void RPN::add(){
	int first = _stack.top();
	_stack.pop();
	int second = _stack.top();
	_stack.pop();
	if(INT_MAX - second < first)
		throw std::runtime_error("Error: Integer overflow occurred.");
	int result = first + second;
	_stack.push(result);
}

void RPN::subtract(){
	int first = _stack.top();
	_stack.pop();
	int second = _stack.top();
	_stack.pop();
	if(INT_MIN + first > second)
		throw std::runtime_error("Error: Integer overflow occurred.");
	int result = second - first;
	_stack.push(result);
}

void RPN::mod(){
	int first = _stack.top();
	_stack.pop();
	int second = _stack.top();
	_stack.pop();
	if(first == 0)
		throw std::runtime_error("Error: Division by zero is not allowed.");
	if(second == INT_MIN && first == -1)
		throw std::runtime_error("Error: Division of INT_MIN by -1.");
	int result = second / first;
	_stack.push(result);
}

void RPN::multiply(){
	int first = _stack.top();
	_stack.pop();
	int second = _stack.top();
	_stack.pop();
	if(first == 0) {
		_stack.push(0);
		return;
	}
	if(INT_MAX / first < second || INT_MIN / first > second)
		throw std::runtime_error("Error: Integer overflow occurred.");
	int result = first * second;
	_stack.push(result);
}
