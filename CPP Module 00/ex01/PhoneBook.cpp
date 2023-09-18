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
	return this->size;
}

bool PhoneBook::Emptystring(Contact contact)
{
	if (contact.getFirstName() == "" || contact.getLastName() == "")
		return (true);
	if (contact.getNickName() == "" || contact.getPhoneNumber() == "")
		return (true);
	if (contact.getDarkestSecret() == "")
		return (true);
	return (false);
}

// 만약 배배열 8이 다 차면 제일 마지막 꺼 없애고 추가
bool PhoneBook::setContactInfo(bool isFull)
{
	std::string str;
	Contact contact;
	int index = this->size;

	std::cout << "First Name : ";
	std::getline(std::cin, str);
	contact.setFirstName(str);
	std::cout << "Last Name : ";
	std::getline(std::cin, str);
	contact.setLastName(str);
	std::cout << "Nick Name : ";
	std::getline(std::cin, str);
	contact.setNickName(str);
	std::cout << "Phone Number : ";
	std::getline(std::cin, str);
	contact.setPhoneNumber(str);
	std::cout << "Darkest Secret : ";
	std::getline(std::cin, str);
	contact.setDarkestSecret(str);
	if (!Emptystring(contact))
	{
		if (isFull)
		{
			for (int i = 1; i < this->size; i++)
			{
				this->contact[i - 1].setAllContact(this->contact[i]);
			}
			index = 7;
		}
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
	if (this->size == 8)
		setContactInfo(true);
	else if (setContactInfo(false))
	{
		this->size++;
	}
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
	for (int i = 0; i < this->size; i++)
	{
		std::string firstName = this->contact[i].getFirstName();
		std::string lastName = this->contact[i].getLastName();
		std::string nickName = this->contact[i].getNickName();
		if (firstName.length() > 10)
			firstName.replace(9, firstName.length() - 9, ".");
		if (lastName.length() > 10)
			lastName.replace(9, lastName.length() - 9, ".");
		if (nickName.length() > 10)
			nickName.replace(9, nickName.length() - 9, ".");
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

void PhoneBook::showDetail()
{
	std::string str;
	std::cout << "[Type Detail List] : ";
	std::getline(std::cin, str);
	for (int i = 0; i < str.length(); i++)
	{
		if (!std::isdigit(str[i]))
		{
			std::cout << "Not number\n";
			return;
		}
	}
	int number = stoi(str);
	if (number < 1 || number > this->size)
	{
		std::cout << "index in range 1 to " << this->size << "\n";
		return;
	}
	std::cout << number << "\n";
	std::cout << "First name : " << this->contact[number - 1].getFirstName() << '\n';
	std::cout << "Last name : " << this->contact[number - 1].getLastName() << '\n';
	std::cout << "Nick name : " << this->contact[number - 1].getNickName() << '\n';
	std::cout << "Phone Number : " << this->contact[number - 1].getPhoneNumber() << '\n';
	std::cout << "DarkestSecret : " << this->contact[number - 1].getDarkestSecret() << '\n';
}