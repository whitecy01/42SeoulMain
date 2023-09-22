#include "Zombie.hpp"

Zombie::Zombie() : name("") // 기본 생성자 구현
{
}

Zombie::Zombie(std::string name) 
{
	this->name = name;
}

Zombie::~Zombie()
{
	std::cout << this->name << " is dead" << std::endl;
}

void Zombie::announce(void)
{
	std::cout << this->name <<  " BraiiiiiiinnnzzzZ..." << std::endl;
}

void	Zombie::setName(std::string name)
{
	this->name = name;
}