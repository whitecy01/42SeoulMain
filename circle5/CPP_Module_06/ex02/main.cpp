#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <ctime>
#include <cstdlib>
#include <iostream>


static Base* generate()
{
	srand(time(NULL));
	int num = rand() % 3;
	switch (num)
	{
		case 0:
			return new A();
			break;
		case 1:
			return new B();
			break;
		case 2:
			return new C();
			break;
		default:
			return NULL;
	}
}

void identify(Base *p)
{
	if (dynamic_cast<A*>(p))
		std::cout << "A\n";
	else if (dynamic_cast<B*>(p))
		std::cout << "B\n";
	else if (dynamic_cast<C*>(p))
		std::cout << "C\n";
}

void identify(Base &p)
{
	try
	{
		A &a = dynamic_cast<A&>(p);
		std::cout << "A\n";
		(void)a;
	}
	catch(const std::exception& e){ }
	try
	{
		B &b = dynamic_cast<B&>(p);
		std::cout << "B\n";
		(void)b;
	}
	catch(const std::exception& e){}
	try
	{
		C &c = dynamic_cast<C&>(p);
		std::cout << "C\n";
		(void)c;
	}
	catch(const std::exception& e){}
	
}

int main()
{
	Base *base = generate();
	std::cout << "identify(Base *p) : ";
	identify(base);
	std::cout << "identify(Base &p) : ";
	identify(*base);

	if (base)
		delete base;
}