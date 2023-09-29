#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

# include <iostream>

class ScavTrap : ClapTrap
{
private:
	std::string name;
	unsigned int hitPoint;
	unsigned int energyPoint;
	unsigned int attackDamage;

public:
	ClapTrap(); // 0
	~ClapTrap(); // 0
	ClapTrap(std::string name); // 0
	ClapTrap(const ClapTrap& ClapTrap); // 0
	ClapTrap& operator=(const ClapTrap& obj);
	void attack(const std::string& target);  // 0
	void takeDamage(unsigned int amount);
	void beRepaired(unsigned int amount);

	std::string getName() const;
	unsigned int getHitPoint() const;
	unsigned int getEnergyPoint() const;
	unsigned int getAttackDamage() const;
};

# endif