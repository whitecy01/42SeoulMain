#include "Cat.hpp"

Cat::Cat(void)
{
	this->type = "Cat";
	std::cout << "Cat Constructor called\n";
}

Cat::Cat(Cat const &cat)
{
	*this = cat;
	std::cout << "Cat Constructor copy called\n";
}

Cat::~Cat()
{
	std::cout << "Cat Destructor called\n";
}

Cat& Cat::operator=(Cat const &cat)
{
	if (this == &cat)
		return *this;
	this->type = cat.getType();
	std::cout << "Cat operator = " << type << " called\n";
	return (*this);
}

void Cat::makeSound(void) const 
{
	std::cout << "nyang\n";	
}