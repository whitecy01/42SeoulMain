#include "Zombie.hpp"

int	main(void)
{
	Zombie stack("stack1");
	Zombie *heap = newZombie("heap");

	randomChump("stack2");
	stack.announce();
	heap->announce();
	delete heap;
	return (0);
}