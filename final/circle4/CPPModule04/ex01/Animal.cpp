#include "Animal.hpp"

Animal::Animal(void)
{
	this->type = "animal";
	std::cout << "Animal Constructor called\n";
}

Animal::Animal(Animal const &animal)
{
	*this = animal;
	std::cout << "Animal Constructor copy called\n";
}

Animal::~Animal()
{
	std::cout << "Animal Destructor called\n";
}

Animal& Animal::operator=(Animal const &animal)
{

	if (this == &animal)
		return *this;
	this->type = animal.getType();
	std::cout << "Animal operator = " << type << " called\n";
	return (*this);
}

std::string Animal::getType(void) const
{
	return (this->type);
}

void Animal::makeSound(void) const 
{
	std::cout << "Animal class can't make sound\n";	
}