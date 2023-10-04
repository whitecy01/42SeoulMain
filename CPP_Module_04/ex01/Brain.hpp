#ifndef BRAIN_HPP
# define BRAIN_HPP

#include "iostream"

class Brain {
private:
	std::string ideas[100];
public:
	Brain();
	Brain(std::string idea);
	Brain(Brain const &brain);
	~Brain();
	Brain &operator=(Brain const &brain);
	std::string getIdea(int index) const;
	void setIdea(int index, std::string str);
};



#endif