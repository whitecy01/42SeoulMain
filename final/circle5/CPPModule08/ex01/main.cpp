#include "Span.hpp"

int main()
{

	std::cout << "================subject=========\n";

	Span sp = Span(5);
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);	
	sp.addNumber(11);

	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;

	std::cout << "========================== N up add ==========================\n";

	Span up = Span(5);
	up.addNumber(6);
	up.addNumber(3);
	up.addNumber(17);
	up.addNumber(9);	
	up.addNumber(11);
	up.addNumber(12);

	std::cout << up.shortestSpan() << std::endl;
	std::cout << up.longestSpan() << std::endl;

	std::cout << "========================== vector size under 2 ==========================\n";
	Span ss = Span(2);
	ss.addNumber(6);

	std::cout << ss.shortestSpan() << std::endl;
	std::cout << ss.longestSpan() << std::endl;

	
	std::cout << "========================== add many in one ==========================\n";
    Span sp2 = Span(10);

	std::vector<int> a;

	a.push_back(1);
	a.push_back(2);
	a.push_back(4);
	a.push_back(5);
	a.push_back(11);
	a.push_back(22);
	a.push_back(41);
	a.push_back(52);	
	a.push_back(1123);
	a.push_back(2231);
	a.push_back(423);
	a.push_back(51);

    sp2.addNumbers(a.begin(), a.end());
    std::cout << sp2.getN() << std::endl;
    sp2.getElement();



	std::cout << "========================== copy ==========================\n";
	Span origin = Span(10);
	origin.addNumber(22);
	origin.addNumber(41);
	origin.addNumber(52);	
	origin.addNumber(1123);
	Span copy(origin);
	copy.addNumber(1111);

	origin.getElement();
	std::cout << "========================== answer ==========================\n";
	copy.getElement();
    
}