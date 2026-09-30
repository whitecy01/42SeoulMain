#include "ScavTrap.hpp"

int	main(void)
{
	ScavTrap a("A");
	ClapTrap b("B");
	ScavTrap c;

	c = a;
	a.attack("B");
	b.takeDamage(0);
	b.takeDamage(2);
	b.beRepaired(2);
	b.takeDamage(10);
	b.takeDamage(50);
	c.attack("B");
	c.guardGate();
}
