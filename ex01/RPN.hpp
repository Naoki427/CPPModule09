#pragma once
#include <iostream>
#include <stack>
#include <climits>

class RPN
{
private:
	std::stack<int> _stack;
public:
	RPN( void );
	RPN(const RPN &origin);
	virtual ~RPN();
	RPN& operator = (const RPN &origin);
	void Calculate(std::string input);
	int add();
	int subtract();
	int mod();
	int multiply();
};