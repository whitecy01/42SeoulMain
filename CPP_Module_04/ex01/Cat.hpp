#ifndef CAT_HPP
# define CAT_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal 
{
private:
	Brain *brain;
public:
	Cat(void);
	Cat(const Cat &cat);
	Cat& operator=(const Cat &cat);
	~Cat(void);
	std::string getCatIdea(int index);
	void setBrain(int index, std::string str);
	void makeSound(void) const;
};

# endif