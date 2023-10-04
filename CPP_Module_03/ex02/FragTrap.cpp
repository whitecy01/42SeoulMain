#include "FragTrap.hpp"

FragTrap::FragTrap() 
{
	this->name = "basic";
	this->hitPoint = 100;
	this->energyPoint = 100;
	this->attackDamage = 30;
	std::cout << "FragTrap " << this->name << " constructor called\n";
}
FragTrap::FragTrap(std::string name)
{
	this->name = name;
	this->hitPoint = 100;
	this->energyPoint = 100;
	this->attackDamage = 30;
	std::cout << "FragTrap " << this->name << " constructor called\n";
}
FragTrap::FragTrap(FragTrap const &fragTrap)
{
	this->name = fragTrap.getName();
	this->hitPoint = fragTrap.getHitPoint();
	this->energyPoint = fragTrap.getEnergyPoint();
	this->attackDamage = fragTrap.getAttackDamage();
	std::cout << "FragTrap " << this->name << " copy constructor called\n";
}
FragTrap& FragTrap::operator=(FragTrap const &obj) 
{
	if (this == &obj)
		return *this;
	this->name = obj.getName();
	this->hitPoint = obj.getHitPoint();
	this->energyPoint = obj.getEnergyPoint();
	this->attackDamage = obj.getAttackDamage();
	std::cout << "FragTrap operator = " << name << " called" << std::endl;
	return (*this);
}
FragTrap::~FragTrap() {
	std::cout << "FragTrap " << this->name << " destructor called\n";
}

void FragTrap::highFivesGuys(void) {
	std::cout << "FragTrap " << this->name << " requests a positive high fives\n";
}