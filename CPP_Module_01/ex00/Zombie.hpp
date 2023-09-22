#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <iostream>

class Zombie
{
	private:
		std::string	_name;
	public:
		Zombie(std::string name23);
		~Zombie();
		void	announce(void);
};

Zombie	*newZombie(std::string nameaa);
void	randomChump(std::string name2);

#endif