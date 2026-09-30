#include "Zombie.hpp"

Zombie	*newZombie(std::string name)
{
	Zombie *result = new Zombie(name);
	return (result);
}