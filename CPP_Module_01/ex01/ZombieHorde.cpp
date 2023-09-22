#include "Zombie.hpp"

Zombie* zombieHorde( int N, std::string name )
{
	Zombie* horde = new Zombie[N];
	std::stringstream	ss;

	for (int i = 0; i < N; i++)
	{
		ss.str(std::string());
		ss << i;
		horde[i].setName(name + ss.str()); 
	}
	// for(int i = 0; i < N; i++)
	// {
	// 	std::cout << i;
	// 	horde[i] = new horde(name);
	// }
	return (horde);
}