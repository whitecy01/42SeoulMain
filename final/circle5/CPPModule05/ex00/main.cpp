#include "Bureaucrat.hpp"

int main()
{
	try 
	{
		Bureaucrat basic;
		std::cout << basic;
	}
	catch (std::exception &e) 
	{
		std::cout << e.what();
	}
	try 
	{
		Bureaucrat normal("A", 75);
		std::cout << normal;
	}
	catch (std::exception &e) 
	{
        std::cout << e.what();
    }
    try 
	{
		Bureaucrat high("A", 151);
		std::cout << high;
    }
	catch (std::exception &e) 
	{
        std::cout << e.what();
    }
    try 
	{
		Bureaucrat low("A", 0);
		std::cout << low;
    }
	catch (std::exception &e) 
	{
		std::cout << e.what();
	}
    return 0;
}