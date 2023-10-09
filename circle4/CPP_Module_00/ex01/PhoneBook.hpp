#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include <iostream>
# include "Contact.hpp"
# include <iomanip>
# include <cstdlib>

class PhoneBook{
private:
	Contact contact[8];
	int size;
	bool setContactInfo();
	bool Emptystring(Contact contact);
	int	 checkspace(std::string str);
public:
	PhoneBook();
	~PhoneBook();
	void startUp();
	void addInfo();
	int  getSize();
	void showInfo();
	void showDetail();
	
};

#endif