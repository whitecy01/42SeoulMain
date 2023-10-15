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
	

	//이게 연산을 했을 때 제일 작은 거 큰 거 인 것 같은데
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;
	
	std::cout << "========================== add many in one ==========================\n";
    Span sp2 = Span(100);
    sp2.addNumbers(100);
    std::cout << sp2.getN() << std::endl;
    sp2.getElement();
    
}