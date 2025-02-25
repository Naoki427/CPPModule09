#pragma once
#include <iostream>
#include <vector>
#include <deque>
#include <climits>
#include <algorithm>
#include <ctime>
#define INVALID_ARG 1
#define UINBT_OVERFLOW 2
#define INCLUDE_ZERO 3


struct Data{
    unsigned int id;
    unsigned int value;
};

class PmergeMe
{
private:
	std::deque<unsigned int> _deque;
	std::vector<unsigned int> _vector;
	PmergeMe( void );
public:
	PmergeMe(int argc,char *argv[]);
	PmergeMe(const PmergeMe &origin);
	virtual ~PmergeMe();
	PmergeMe& operator = (const PmergeMe &origin);
	std::deque<unsigned int> getDeque() const;
	std::vector<unsigned int> getVector() const;

	int isNumber(char *arg);
	int power(int base, int exponent);
	void swapBigSmall(unsigned int &big, unsigned int &small);
	int checkDuplicate(std::vector<unsigned int> &vec);

	void vectorInit(int argc,char *argv[]);
	void initValueV(std::vector<unsigned int>::iterator start,std::vector<unsigned int>::iterator end, std::vector<Data>& vec);
	void vectorSort(std::vector<unsigned int> &vec);
	void insertVectorElement(std::vector<unsigned int>& vec, unsigned int element, int left, int right);
	int getSmallIndexV(unsigned int value, const std::vector<Data>& small);
	int findLeftV(std::vector<unsigned int>& vec, unsigned int value);

	void dequeInit(int argc,char *argv[]);
	void initValueD(std::deque<unsigned int>::iterator start,std::deque<unsigned int>::iterator end, std::deque<Data>& deq);
	void dequeSort(std::deque<unsigned int> &deq);
	void insertDequeElement(std::deque<unsigned int>& deq, unsigned int element, int left, int right);
	int getSmallIndexD(unsigned int value, const std::deque<Data>& small);
	int findLeftD(std::deque<unsigned int>& deq, unsigned int value);

	void diplay();

};