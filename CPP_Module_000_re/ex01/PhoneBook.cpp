#include "PhoneBook.hpp"

PhoneBook::PhoneBook()
{
	this->size = 0;
}

PhoneBook::~PhoneBook()
{
}

void PhoneBook::startUp()
{
	std::cout << "Phonebook Program\n";
	std::cout << "please enter your command : (ADD, SEARCH, EXIT)\n";
}

int PhoneBook::getSize()
{
	return (this->size);
}

bool PhoneBook::Emptystring(Contact contact)
{
	if (contact.getFirstName() == "" || contact.getLastName() == "" || \
		checkspace(contact.getFirstName()) || checkspace(contact.getLastName()))
		return (true);
	if (contact.getNickName() == "" || contact.getPhoneNumber() == "" || \
		checkspace(contact.getNickName()) || checkspace(contact.getPhoneNumber()))
		return (true);
	if (contact.getDarkestSecret() == "" || checkspace(contact.getDarkestSecret()))
		return (true);
	return (false);
}

int	PhoneBook::checkspace(std::string str)
{
	for (int i = 0; i < string_length(str); i++)
	{
		if (str[i] != ' ')
		{
			return (0);
		}
	}
	return (1);
}

bool PhoneBook::setContactInfo()
{
	std::string str;
	Contact contact;
	int index = this->size % 8;

	std::cout << "First Name : ";
	std::getline(std::cin, str);
	if (std::cin.fail())
		return (0);
	contact.setFirstName(str);
	std::cout << "Last Name : ";
	std::getline(std::cin, str);
	if (std::cin.fail())
		return (0);
	contact.setLastName(str);
	std::cout << "Nick Name : ";
	std::getline(std::cin, str);
	if (std::cin.fail())
		return (0);
	contact.setNickName(str);
	std::cout << "Phone Number : ";
	std::getline(std::cin, str);
	if (std::cin.fail())
		return (0);
	contact.setPhoneNumber(str);
	std::cout << "Darkest Secret : ";
	std::getline(std::cin, str);
	if (std::cin.fail())
		return (0);
	contact.setDarkestSecret(str);

	if (!Emptystring(contact))
	{
		this->contact[index].setFirstName(contact.getFirstName());
		this->contact[index].setLastName(contact.getLastName());
		this->contact[index].setNickName(contact.getNickName());
		this->contact[index].setPhoneNumber(contact.getPhoneNumber());
		this->contact[index].setDarkestSecret(contact.getDarkestSecret());
		return true;
	}
	else
	{
		std::cout << "Empty string\n";
		return (false);
	}
}

void PhoneBook::addInfo()
{
	if (setContactInfo())
		this->size++;
}

void PhoneBook::showInfo()
{

	std::cout << "============================================="
			  << "\n";
	std::cout << "|" << std::setw(10) << "index"
			  << "|" << std::setw(10) << "first name"
			  << "|";
	std::cout << std::setw(10) << "last name"
			  << "|" << std::setw(10) << "nick name"
			  << "|"
			  << "\n";
	std::cout << "---------------------------------------------"
			  << "\n";
	for (int i = 0; i < this->size && i < 8; i++)
	{
		std::string firstName = this->contact[i].getFirstName();
		std::string lastName = this->contact[i].getLastName();
		std::string nickName = this->contact[i].getNickName();
		if (string_length(firstName) > 10)
			//firstName.replace(9, firstName.length() - 9, ".");
			firstName = firstName.substr(0, 9) + ".";
		if (string_length(lastName) > 10)
			//lastName.replace(9, lastName.length() - 9, ".");
			lastName = lastName.substr(0, 9) + ".";
		if (string_length(nickName) > 10)
			//nickName.replace(9, nickName.length() - 9, ".");
			nickName = nickName.substr(0, 9) + ".";
		std::cout << "|";
		std::cout << std::setw(10) << i + 1 << "|";
		std::cout << std::setw(10) << firstName << "|";
		std::cout << std::setw(10) << lastName << "|";
		std::cout << std::setw(10) << nickName << "|";
		std::cout << "\n";
	}
	std::cout << "---------------------------------------------"
			  << "\n";
}

int	PhoneBook::string_length(std::string str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

void PhoneBook::showDetail()
{
	std::string str;
	std::cout << "[Type Detail List] : ";
	std::getline(std::cin, str);
	if (std::cin.fail())
		return ;
	for (int i = 0; i < string_length(str); i++)
	{
		if (!std::isdigit(str[i]))
		{
			std::cout << "Not number\n";
			return;
		}
	}
	const char *ptr = &str[0];
	int	number;

	number = atoi(ptr);


	if (!(number <= 8 && number >= 1 && number <= this->size))
	{
		std::cout << "Out of range" << "\n";
		return;
	}
	std::cout << "First name : " << this->contact[number - 1].getFirstName() << '\n';
	std::cout << "Last name : " << this->contact[number - 1].getLastName() << '\n';
	std::cout << "Nick name : " << this->contact[number - 1].getNickName() << '\n';
	std::cout << "Phone Number : " << this->contact[number - 1].getPhoneNumber() << '\n';
	std::cout << "DarkestSecret : " << this->contact[number - 1].getDarkestSecret() << '\n';
}