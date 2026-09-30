#include "Dog.hpp"
#include "Brain.hpp"

Dog::Dog(void)
{
	this->type = "Dog";
	this->brain = new Brain();
	std::cout << "Dog Constructor called\n";
}

Dog::Dog(Dog const &dog)
{
	this->brain = new Brain();
	*this = dog;
	std::cout << "Dog Constructor copy called\n";
}

Dog::~Dog()
{
	delete brain;
	std::cout << "Dog Destructor called\n";
}

Dog& Dog::operator=(Dog const &dog)
{
	if (this == &dog)
		return *this;
	this->type = dog.getType();
	if (this->brain)
	{
		delete this->brain;
	}
	this->brain = new Brain(*(dog.brain));
	std::cout << "Dog operator = " << type << " called\n";
	return (*this);
}


std::string Dog::getDogIdea(int index)
{	
	if (index >= 100)
	{
		std::cout << "99 out of range\n";
		return "";
	}
	return brain->getIdea(index);
}

void Dog::setBrain(int index, std::string str)
{
	if (index >= 100)
	{
		std::cout << "99 out of range\n";
		return ;
	}
	brain->setIdea(index, str);
}

void Dog::makeSound(void) const 
{
	std::cout << "meong\n";	
}
