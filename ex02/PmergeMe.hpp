#pragma once
#include <iostream>
#include <vector>
#include <deque>
#include <climits>
#include <algorithm> 
#define INVALID_ARG 1
#define UINBT_OVERFLOW 2


struct Data{
    unsigned int id;
    unsigned int value;
};

class PmergeMe
{
private:
	std::deque<unsigned int> _deque;
	PmergeMe( void );
public:
	std::vector<unsigned int> _vector;
	PmergeMe(int argc,char *argv[]);
	PmergeMe(const PmergeMe &origin);
	virtual ~PmergeMe();
	PmergeMe& operator = (const PmergeMe &origin);
	void vectorInit(int argc,char *argv[]);
	int isNumber(char *arg);
	int power(int base, int exponent);
	void vectorSort(std::vector<unsigned int> &vec);
	void insertVectorElement(std::vector<unsigned int>& vec, unsigned int element, int left, int right);
	void initValueV(std::vector<unsigned int>::iterator start,std::vector<unsigned int>::iterator end, std::vector<Data>& vec);
	void swapBigSmallV(unsigned int &big, unsigned int &small);
	int getSmallIndexV(unsigned int value, const std::vector<Data>& small);
};