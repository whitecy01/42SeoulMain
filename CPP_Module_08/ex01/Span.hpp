#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <algorithm>
#include <iostream>


class Span{
private:
	std::vector<int> vec;
	unsigned int N;

public:

	Span();
	Span(unsigned int N);
	Span(Span const &span);
	~Span();
	Span& operator=(Span const &span);
	

	void addNumber(int num);
	bool checkDup(int num) ;

	int shortestSpan() const;
	int longestSpan() const;

	std::vector<int> sortVector() const;

	unsigned int getN() const;

};

#endif