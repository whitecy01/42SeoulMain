#include "Warlock.hpp"


Warlock::Warlock()
{

}

Warlock::Warlock(std::string name, std::string title)
{
    this->name = name;
    this->title = title;
    std::cout << this->name << ": This looks like another boring day." << std::endl;
}


Warlock::~Warlock()
{
    std::cout << this->name << ": My job here is done!" << std::endl;
}

Warlock::Warlock(const Warlock &warlock)
{
    *this = warlock;
}

Warlock &Warlock::operator=(const Warlock &warlock)
{
    if (this == &warlock)
        return (*this);
    this->name = warlock.getName();
    this->title = warlock.getTitle();
    return *this;
}

void Warlock::introduce() const 
{
    std::cout << this->name << ": I am " << this->name << ", " << this->title << "!" << std::endl;
}

std::string Warlock::getName() const
{
    return this->name;
}

void Warlock::setTitle(std::string const &title)
{
    this->title = title;
}

std::string Warlock::getTitle() const
{
    return this->title;
}