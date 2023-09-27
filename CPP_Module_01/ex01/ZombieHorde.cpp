#include "Zombie.hpp"

Zombie* zombieHorde(int N, std::string name)
{
	if (N <= 0)
	{
		std::cout << "Please enter a positive value\n";
		return (NULL);
	}
	Zombie* horde = new Zombie[N];

	for (int i = 0; i < N; i++)
	{
		std::cout << i;
		horde[i].setName(name); 
		std::cout << name << '\n';
	}
	return (horde);
}