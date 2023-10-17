#include <iostream>
#include <map>

int main()
{
	std::map <std::string , int > map_loc;

	map_loc.insert(std::make_pair("jaeyojun", 23));

	if (map_loc.find("jaeyojun") != map_loc.end())
	{
		std::cout << "awd" << std::endl;
	}
	else
		std::cout << "fuck\n";

	map_loc.erase("jaeyojun");
	if (map_loc.find("jaeyojun") != map_loc.end())
	{
		std::cout << "awd" << std::endl;
	}
	else
		std::cout << "fuck\n";
}