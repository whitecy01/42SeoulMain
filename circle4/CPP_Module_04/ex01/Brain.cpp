#include "Brain.hpp"

Brain::Brain(void) {
	std::cout << "Brain Constructor called\n";
	for (int i = 0; i < 100; i++)
	{
		this->ideas[i] = "nothing";
	}
}
Brain::Brain(std::string idea) 
{
	std::cout << "Brain Constructor called\n";
	for (int i = 0; i < 100; i++)
	{
		this->ideas[i] = idea;
	}
}

Brain::Brain(Brain const &brain) {
	*this = brain;
}

Brain::~Brain(void) {
	std::cout << "Brain Destructor called\n";
}

Brain& Brain::operator=(Brain const &brain) {
	if (this == &brain) 
		return *this;
	for (int i = 0; i < 100; i++) {
		this->ideas[i] = brain.getIdea(i);
	}
	return (*this);

}

std::string Brain::getIdea(int index) const
{
	return this->ideas[index];
}

void Brain::setIdea(int index, std::string str)
{
	ideas[index] = str;
}