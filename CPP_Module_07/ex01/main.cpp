#include "whatever.hpp"
#include <iostream>

int main()
{
	int a = 2;
	int b = 3;


	std::cout << "swap [Before]\n";
	std::cout << "a : " << a << "\n";
	std::cout << "b : " << b << "\n"; 
	swap(a, b);
	std::cout << "swap [After]\n";
	std::cout << "a : " << a << "\n";
	std::cout << "b : " << b << "\n"; 

	std::cout << "========================\n";

	std::cout << "min : ";
	std::cout << min(a, b) << "\n";

	std::cout << "max : ";
	std::cout << max(a, b) << "\n";


}