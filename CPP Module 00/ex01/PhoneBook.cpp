#include "PhoneBook.hpp"

void PhoneBook::startUp(){
	std::cout << "Phonebook Program" << std::endl;
	std::cout << "please enter your command : (ADD, SEARCH, EXIT)" << std::endl;
}

//만약 배배열 8이 다 차면 제일 마지막 꺼 없애고 추가
void PhoneBook::addInfo(){
	std::string	str;
	Contact contact;

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
	this->contact[0].setFirstName(contact.getFirstName());
}


void PhoneBook::showInfo()
{
	std::string f;
	
	f = contact[0].getFirstName();
	std::cout << f;
}