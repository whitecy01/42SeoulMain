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

void Span::addNumbers(int num)
{
	while (num > 0)
	{
		int random = rand();
		try
		{
			addNumber(random);
			num--;
		}
		catch(const std::exception& e) { }
	}
}

int Span::shortestSpan() const
{
	if (this->vec.size() < 2)
		throw std::runtime_error("size is under 2");
	std::vector<int> sorted = sortVector();
	long ret = LONG_MAX;
	int prev;
	for (std::vector<int>::iterator iter = sorted.begin(); iter != sorted.end(); iter++)
	{
		if (iter == sorted.begin())
		{
			prev = *iter;
		}
		else
		{
			if (ret > *iter - prev)
			{
				ret = *iter - prev;
			}
			prev = *iter;
		}
	}

	return ret;
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

void Span::getElement() const
{
	for (unsigned int i = 0; i < N; i++)
	{
		std::cout << vec[i] << "\n";
	}
	
}


unsigned int Span::getN() const 
{
	return this->N;
}
