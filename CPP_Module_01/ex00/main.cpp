#include "Zombie.hpp"

int	main(void)
{
	Zombie zombie_stack("Foo");
	Zombie *heap_zombie = newZombie("heap_zombie");
	
	randomChump("fun_zombie");
	zombie_stack.announce();
	heap_zombie->announce();
	delete heap_zombie;
	return (0);
}