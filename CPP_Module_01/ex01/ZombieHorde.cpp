#include "Zombie.hpp"

Zombie* zombieHorde( int N, std::string name )
{
	Zombie* horde = new Zombie[N];

	for (int i = 0; i < N; i++)
	{
		std::cout << i;
		horde[i].setName(name); 
		std::cout << name << '\n';
	}
	return (horde);
}