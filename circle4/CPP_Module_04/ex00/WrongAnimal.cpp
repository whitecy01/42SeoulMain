#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal(void)
{
	this->type = "WrongAnimal";
	std::cout << "WrongAnimal Constructor called\n";
}

WrongAnimal::WrongAnimal(WrongAnimal const &wrongAnimal)
{
	*this = wrongAnimal;
	std::cout << "WrongAnimal Constructor copy called\n";
}

WrongAnimal::~WrongAnimal()
{
	std::cout << "WrongAnimal Destructor called\n";
}

WrongAnimal& WrongAnimal::operator=(WrongAnimal const &wrongAnimal)
{
	if (this == &wrongAnimal)
		return *this;
	this->type = wrongAnimal.getType();
	std::cout << "WrongAnimal operator = " << type << " called\n";
	return (*this);
}

std::string WrongAnimal::getType(void) const
{
	return (this->type);
}

void WrongAnimal::makeSound(void) const 
{
	std::cout << "WrongAnimal class can't make sound\n";	
}