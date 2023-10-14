#include "Span.hpp"

Span::Span()
{	 
	N = 0;
}

Span::Span(unsigned int N) :  N(N)
{

}

Span::~Span()
{

}

Span::Span(Span const &span)
{
	*this = span;
}

Span& Span::operator=(Span const &span)
{
	if (this == &span)
		return *this;
	this->N = span.N;
	this->vec = span.vec;
	return *this;
}


bool Span::checkDup(int num) 
{
	for (std::vector<int>::iterator iter = vec.begin(); iter != vec.end(); iter++)
	{
		if (num == *iter)
			return true;
	}
	return false;
}

void Span::addNumber(int num)
{
	if (checkDup(num))
	{
		throw std::runtime_error("it's already inside\n");
	}
	vec.push_back(num);
}

int Span::shortestSpan() const
{
	if (this->vec.size() < 2)
		throw std::runtime_error("size is under 2");
	std::vector<int> sorted = sortVector();
	std::vector<int>::const_iterator iter = sorted.begin();

	return *iter;
}

int Span::longestSpan() const 
{
	if (this->vec.size() < 2)
		throw std::runtime_error("size is under 2");
	return (*std::max_element(this->vec.begin(), this->vec.end()) - *std::min_element(this->vec.begin(), this->vec.end()));
}

std::vector<int> Span::sortVector() const
{
	std::vector <int> sorted(this->vec);
	std::sort(sorted.begin(), sorted.end());
	return sorted;
}


unsigned int Span::getN() const 
{
	return this->N;
}
