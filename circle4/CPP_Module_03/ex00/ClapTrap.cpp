#include "ClapTrap.hpp"

ClapTrap::ClapTrap() {
	this->name = "basic";
	this->hitPoint = 10;
	this->energyPoint = 10;
	this->attackDamage = 0;

	std::cout << "ClapTrap " << this->name << " constructor called\n";
}

ClapTrap::ClapTrap(std::string name) {
	this->name = name;
	this->hitPoint = 10;
	this->energyPoint = 10;
	this->attackDamage = 0;

	std::cout << "ClapTrap " << this->name << " constructor called\n";
}

ClapTrap::ClapTrap(ClapTrap const &obj) {
	this->name = obj.getName();
	this->hitPoint = obj.getHitPoint();
	this->energyPoint = obj.getEnergyPoint();
	this->attackDamage = obj.getAttackDamage();
	std::cout << "ClapTrap " << this->name << " copy constructor called\n";
}

ClapTrap::~ClapTrap(){
	std::cout << "ClapTrap " << this->name << " destructor called\n";
}

ClapTrap& ClapTrap::operator=(const ClapTrap &obj) {
	if (this == &obj)
		return *this;
	this->name = obj.getName();
	this->attackDamage = obj.getAttackDamage();
	this->hitPoint = obj.getHitPoint();
	this->energyPoint = obj.getEnergyPoint();
	std::cout << "ClapTrap operator = " << name << " called" << std::endl;
	return (*this);
}

void	ClapTrap::attack(const std::string& target) {
	if (!this->hitPoint) {
		std::cout << "ClapTrap " << this->name << " has no hitPoint died" << std::endl;
		return ;
	}
	if (!this->energyPoint) {
		std::cout << "ClapTrap " << this->name << " has no Energy Points\n" << std::endl;
		return ;
	}
	
	std::cout << "ClapTrap " << this->name << " attacks " << target;
	std::cout << ", causing " << this->attackDamage << " points of damage!\n";
	this->energyPoint--;
}

void	ClapTrap::takeDamage(unsigned int amount) {
	if (!this->hitPoint){
		std::cout << "ClapTrap " << this->name << " has no hitPoint died" << std::endl;
		return ;
	}
	if (this->hitPoint < amount)
		this->hitPoint = 0;
	else
		this->hitPoint -= amount;
	std::cout << "ClapTrap " << this->name << " has taken Damage " << amount << "\n";
	if (!this->hitPoint)
		std::cout << "ClapTrap " << this->name << " died\n";
}


void	ClapTrap::beRepaired(unsigned int amount) {
	if (!this->hitPoint) {
		std::cout << "ClapTrap " << this->name << " has no hitPoint died" << std::endl;
		return ;
	}
	if (!this->energyPoint) {
		std::cout << "ClapTrap " << this->name << " has no Energy Points" << std::endl;
		return ;
	}
	
	this->hitPoint += amount;
	this->energyPoint--;
	std::cout << "ClapTrap " << this->name << " has been repaired of " << amount << " His points. It has now " \
		<< this->hitPoint << " Hit points" << std::endl;
}

std::string ClapTrap::getName() const {
	return this->name;
}

unsigned int ClapTrap::getHitPoint() const {
	return this->hitPoint;
}

unsigned int ClapTrap::getEnergyPoint() const {
	return this->energyPoint;
}

unsigned int ClapTrap::getAttackDamage() const {
	return this->attackDamage;
}
