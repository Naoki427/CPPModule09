#pragma once
#include <iostream>
#include <stack>
#include <list>
#include <climits>

class RPN
{
private:
	std::stack<int, std::list<int> > _stack;
public:
	RPN( void );
	RPN(const RPN &origin);
	virtual ~RPN();
	RPN& operator = (const RPN &origin);
	std::stack<int, std::list<int> > getStack() const;
	void Calculate(std::string input);
	void add();
	void subtract();
	void mod();
	void multiply();
};