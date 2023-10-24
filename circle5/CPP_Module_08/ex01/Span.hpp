#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <algorithm>
#include <iostream>
#include <limits.h>

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
	template <typename s>
	void addNumbers(s b, s end)
	{
		for (; b != end; b++)
		{
			addNumber(*b);
		}
	}

	int shortestSpan() const;
	int longestSpan() const;

	std::vector<int> sortVector() const;

	unsigned int getN() const;
	void getElement() const;

};

#endif