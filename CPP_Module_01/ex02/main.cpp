#include <iostream>

int	main(void)
{
	std::string str = "HI THIS IS BRAIN";
	std::string *stringPTR = &str;
	std::string &stringREF = str;

	std::cout << "Print Memory address" << std::endl;
	std::cout << "str address : " << &str << std::endl;
	std::cout << "stringPRT address : " << stringPTR << std::endl;
	std::cout << "stringREF address : " << &stringREF << std::endl;

	std::cout << std::endl;
	std::cout << "str value : " << str << std::endl;
	std::cout << "stringPRT value : " << *stringPTR << std::endl;
	std::cout << "stringREF value : " << stringREF << std::endl; 
}