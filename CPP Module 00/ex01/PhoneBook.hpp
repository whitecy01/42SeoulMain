#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include <iostream>
# include <string>
# include "Contact.hpp"

class PhoneBook{
private:
	Contact contact[8];
	int size;
public:


	void startUp();
	void addInfo();
	void setContactInfo();
	void showInfo();
};

#endif