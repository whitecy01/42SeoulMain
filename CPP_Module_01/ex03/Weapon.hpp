#ifndef WEAPON_HPP
# define WEAPON_HPP

#include <iostream>

class Weapon{
	private:
		std::string type;
	public:
	Weapon();
	Weapon(std::string type);
	~Weapon();
	const std::string &getType(void) const;
	void setType(const std::string type);
};

#endif