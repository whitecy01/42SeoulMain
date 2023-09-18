#ifndef CONTACT_HPP
# define CONTACT_HPP

#include <iostream>

class Contact{
private:
	std::string First_name;
	std::string last_name;
	std::string nick_name;
	std::string phone_number;
	std::string darkset_secret;
public:
	
	void	setFirstName(std::string First_Name);
	void	setLastName(std::string last_name);
	void	setNickName(std::string nick_name);
	void	setPhoneNumber(std::string phone_number);
	void	setDarkestSecret(std::string darkset_secret);

	std::string getFirstName();
	std::string getLastName();
	std::string getNickName();
	std::string getPhoneNumber();
	std::string getDarkestSecret();

	void	setAllContact(Contact contact);
};

#endif