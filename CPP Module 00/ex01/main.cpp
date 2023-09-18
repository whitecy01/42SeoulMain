#include "PhoneBook.hpp"

int main(void)
{
	PhoneBook phoneBook;
	std::string temp;

	while (1)
	{
		phoneBook.startUp();
		std::getline(std::cin, temp);
		if (std::cin.eof())
		{
			std::cout << "EOF meet finish" << std::endl;
			return (0); 
		}
		if (temp == "ADD")
			phoneBook.addInfo();
		else if (temp == "SEARCH")
		{
			if (phoneBook.getSize() == 0)
			{
				std::cout << "Nothing Added. Add First\n";
				continue;
			}
			phoneBook.showInfo();
			phoneBook.showDetail();
		}
		else if (temp == "EXIT")
		{
			std::cout << "Program EXIT" << "\n";
			return (0);
		}
	}
}