#include "Span.hpp"

Span::Span()
{
	N = 0;
}

Span::Span(unsigned int N) : N(N)
{
}

Span::~Span()
{
}

Span::Span(Span const &span)
{
	*this = span;
}

Span &Span::operator=(Span const &span)
{
	if (this == &span)
		return *this;
	this->N = span.N;
	this->vec = span.vec;
	return *this;
}

void Span::addNumber(int num)
{
	try
	{
		if (vec.size() >= this->N)
		{
			throw std::runtime_error("The size of the vector exceeds N");
		}
		vec.push_back(num);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
}

int Span::shortestSpan() const
{
	try
	{
		if (this->vec.size() < 2)
			throw std::runtime_error("vector size is under 2");
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
		return 0;
	}
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
			ret = std::min(ret, static_cast<long>(*iter - prev));
			prev = *iter;
		}
	}
	return ret;
}

int Span::longestSpan() const
{
	try
	{
		if (this->vec.size() < 2)
			throw std::runtime_error("size is under 2");
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
		return 0;
	}
	return (*std::max_element(this->vec.begin(), this->vec.end()) - *std::min_element(this->vec.begin(), this->vec.end()));
}

std::vector<int> Span::sortVector() const
{
	std::vector<int> sorted(this->vec);
	std::sort(sorted.begin(), sorted.end());
	return sorted;
}

void Span::getElement() const
{
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i] << "\n";
	}
}

unsigned int Span::getN() const
{
	return this->N;
}
