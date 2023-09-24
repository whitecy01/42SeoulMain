#include "HumanB.hpp"


HumanB::HumanB(std::string name) {this->name = name;}

HumanB::~HumanB(){}

void HumanB::setWeapon(Weapon &weapon){ this->weapon = &weapon;}

void HumanB::attack(void) const
{
	std::cout << this->name << " attacks with his " << this->weapon->getType() << std::endl;
}