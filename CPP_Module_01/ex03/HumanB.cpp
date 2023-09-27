#include "HumanB.hpp"


HumanB::HumanB(std::string name) 
{
	this->name = name;
	this->weapon = NULL;
}

HumanB::~HumanB(){}

void HumanB::setWeapon(Weapon &weapon){ this->weapon = &weapon;}

void HumanB::attack(void) const
{
	if (weapon == NULL)
    {
        std::cout << this->name << " attacks with a hit hand " << std::endl;
		return ;
	}
    else
    {
        std::cout << this->name << " attacks with a " << this->weapon->getType() << std::endl;
    }
}