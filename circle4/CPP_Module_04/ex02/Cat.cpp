#include "Cat.hpp"

Cat::Cat(void)
{
	this->type = "Cat";
	this->brain = new Brain();
;	std::cout << "Cat Constructor called\n";
}

Cat::Cat(Cat const &cat)
{
	this->brain = new Brain();
	*this = cat;
	std::cout << "Cat Constructor copy called\n";
}

Cat::~Cat()
{
	delete brain;
	std::cout << "Cat Destructor called\n";
}

Cat& Cat::operator=(Cat const &cat)
{
	if (this == &cat)
		return *this;
	this->type = cat.getType();
	if (this->brain)
	{
		delete this->brain;
	}
	this->brain = new Brain(*(cat.brain));
	std::cout << "Cat operator = " << type << " called\n";
	return (*this);
}

std::string Cat::getCatIdea(int index)
{	
	if (index >= 100)
	{
		std::cout << "99 out of range\n";
		return "";
	}
	return brain->getIdea(index);
}

void Cat::setBrain(int index, std::string str)
{
	if (index >= 100)
	{
		std::cout << "99 out of range\n";
		return ;
	}
	brain->setIdea(index, str);
}

void Cat::makeSound(void) const 
{
	std::cout << "nyang\n";	
}