#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include <iostream>
# include "Contact.hpp"
# include <iomanip>
#include <string>

class PhoneBook{
private:
	Contact contact[8];
	int size;
public:

	PhoneBook();
	~PhoneBook();
	void startUp();
	void addInfo();
	int  getSize();
	bool setContactInfo();
	bool Emptystring(Contact contact);
	void showInfo();
	void showDetail();
	int	 checkspace(std::string str);
	
};

#endif