#include "Contact.hpp"

void	Contact::setFirstName(std::string First_name){
	this->First_name = First_name;
}

void	Contact::setLastName(std::string last_name){
	this->last_name = last_name;
}

void	Contact::setNickName(std::string nick_name){
	this->nick_name = nick_name;
}

void	Contact::setPhoneNumber(std::string phone_number){
	this->phone_number = phone_number;
}

void	Contact::setDarkestSecret(std::string darkset_secret){
	this->darkset_secret = darkset_secret;
}

std::string Contact::getFirstName() {return this->First_name;}