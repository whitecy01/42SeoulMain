#include "HumanA.hpp"



HumanA::HumanA(std::string name, Weapon &weapon) : name(name), weapon(weapon)
{
}

HumanA::~HumanA(){}

void HumanA::attack() const
{
	std::cout << this->name << " attacks with this " << this->weapon.getType() << std::endl;
}