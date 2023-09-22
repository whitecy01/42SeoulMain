#include "Contact.hpp"

void	Contact::setFirstName(std::string first_name){
	this->first_name = first_name;
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

std::string Contact::getFirstName() {return this->first_name;}
std::string Contact::getLastName() {return this->last_name;}
std::string Contact::getNickName() {return this->nick_name;}
std::string Contact::getPhoneNumber() {return this->phone_number;}
std::string Contact::getDarkestSecret() {return this->darkset_secret;}


void	Contact::setAllContact(Contact contact)
{
	this->first_name = contact.first_name;
	this->last_name = contact.last_name;
	this->nick_name = contact.nick_name;
	this->phone_number = contact.phone_number;
	this->darkset_secret = contact.darkset_secret;
}