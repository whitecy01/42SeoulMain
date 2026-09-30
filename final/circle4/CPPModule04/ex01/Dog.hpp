#ifndef DOG_HPP
# define DOG_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal
{
private:
	Brain *brain;
public:
	Dog(void);
	Dog(const Dog &dog);
	Dog& operator=(const Dog &dog);
	void setBrain(int index, std::string str);
	std::string getDogIdea(int index);
	~Dog(void);
	void makeSound(void) const;
};

# endif