#include "WrongCat.hpp"

WrongCat::WrongCat(void)
{
	this->type = "WrongCat";
	std::cout << "WrongCat Constructor called\n";
}

WrongCat::WrongCat(WrongCat const &wrongCat)
{
	*this = wrongCat;
	std::cout << "WrongCat Constructor copy called\n";
}

WrongCat::~WrongCat()
{
	std::cout << "WrongCat Destructor called\n";
}

WrongCat& WrongCat::operator=(WrongCat const &wrongCat)
{
	if (this == &wrongCat)
		return *this;
	this->type = wrongCat.getType();
	std::cout << "WrongCat operator = " << type << " called\n";
	return (*this);
}

void WrongCat::makeSound(void) const 
{
	std::cout << "WrongCat class can't make sound\n";
}