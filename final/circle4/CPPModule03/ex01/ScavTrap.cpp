#include "ScavTrap.hpp"

ScavTrap::ScavTrap()
{
	this->name = "basic";
	this->hitPoint = 100;
	this->energyPoint = 50;
	this->attackDamage = 20;

	std::cout << "ScavTrap " << this->name << " constructor called\n";
}

ScavTrap::ScavTrap(std::string name)
{
	this->name = name;
	this->hitPoint = 100;
	this->energyPoint = 50;
	this->attackDamage = 20;

	std::cout << "ScavTrap " << this->name << " constructor called\n";
}

ScavTrap::ScavTrap(ScavTrap const &scavTrap)
{
	this->name = scavTrap.getName();
	this->hitPoint = scavTrap.getHitPoint();
	this->energyPoint = scavTrap.getEnergyPoint();
	this->attackDamage = scavTrap.getAttackDamage();

	std::cout << "ScavTrap " << this->name << " copy constructor called\n";
}

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap " << this->name << " destructor called\n";
}
ScavTrap& ScavTrap::operator=(const ScavTrap &ScavTrap)
{
	if (this == &ScavTrap)
		return *this;
	this->name = ScavTrap.getName();
	this->attackDamage = ScavTrap.getAttackDamage();
	this->hitPoint = ScavTrap.getHitPoint();
	this->energyPoint = ScavTrap.getEnergyPoint();
	std::cout << "ScavTrap operator = " << name << " called" << std::endl;
	return (*this);
}

void ScavTrap::attack(const std::string &target)
{
	if (!this->hitPoint)
	{
		std::cout << "ScavTrap " << this->name << " has no hitPoint died" << std::endl;
	}
	else if (!this->energyPoint)
	{
		std::cout << "ScavTrap " << this->name << " has no Energy Points" << std::endl;
	}
	else
	{
		std::cout << "ScavTrap " << this->name << " attacks " << target;
		std::cout << ", causing " << this->attackDamage << " points of damage!\n";
		this->energyPoint--;
	}
}

void ScavTrap::guardGate()
{
	if (!this->hitPoint)
	{
		std::cout << "ScavTrap " << this->name << " has no hitPoint died\n" << std::endl;
	}
	else if (!this->energyPoint)
	{
		std::cout << "ScavTrap " << this->name << " has no Energy Points\n" << std::endl;
	}
	else
	{
		std::cout << "ScavTrap " << this->name << " is now in Gate Keeper mode.\n";
	}
}