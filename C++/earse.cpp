#include <iostream>

#include <fstream>

int main()
{
	std::string name = "rgdrgdrgdrg 123 bbbb";

	name.erase(12, 3);
	name.insert(12, "aaa");
	std::cout << name << "\n";
}