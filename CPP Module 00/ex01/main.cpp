#include "PhoneBook.hpp"

int main(void)
{
	PhoneBook phoneBook;
	std::string temp;
	while (1)
	{
		phoneBook.startUp();
		std::getline(std::cin, temp);
		if (temp == "ADD")
			phoneBook.addInfo();
		else if (temp == "SEARCH")
		{
			phoneBook.showInfo();
		}
		else if (temp == "EXIT")
		{
			std::cout << "Program EXIT" << std::endl;
			return (1);
		}

	}
}