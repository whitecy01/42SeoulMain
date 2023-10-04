#include "Dog.hpp"

Dog::Dog(void)
{
	this->type = "Dog";
	std::cout << "Dog Constructor called\n";
}

Dog::Dog(Dog const &dog)
{
	*this = dog;
	std::cout << "Dog Constructor copy called\n";
}

Dog::~Dog()
{
	std::cout << "Dog Destructor called\n";
}

Dog& Dog::operator=(Dog const &dog)
{
	if (this == &dog)
		return *this;
	this->type = dog.getType();
	std::cout << "Dog operator = " << type << " called\n";
	return (*this);
}

void Dog::makeSound(void) const 
{
	std::cout << "meong\n";	
}