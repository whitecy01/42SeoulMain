#include "Warlock.hpp"

Warlock::Warlock(std::string name, std::string title) : name(name), title(title)
{
    std::cout << name << ": This looks like another boring day." << std::endl;
}

Warlock::Warlock()
{}

Warlock::~Warlock()
{
    std::cout<< name << ": My job here is done!" << std::endl;
    for (std::map<std::string, ASpell *>::iterator iter = _SpellBook.begin(); iter != _SpellBook.end(); ++iter)
    {
        delete iter->second;
    }
    _SpellBook.clear();
}

Warlock::Warlock(Warlock const &warlock)
{
    *this = warlock;
}

Warlock &Warlock::operator=(Warlock const &warlock)
{
    if (this == &warlock)
        return *this;
    name = warlock.name;
    title = warlock.title;
    return *this;
}

std::string const &Warlock::getName() const
{
    return this->name;
}

std::string const &Warlock::getTitle() const
{
    return this->title;
}

void Warlock::setTitle(std::string const &title)
{
    this->title = title;
}

void Warlock::introduce() const
{
    std::cout << name << ": I am " <<name << ", " << title << "!" <<std::endl; 
}

void Warlock::learnSpell(ASpell *aspell)
{
    if (aspell)
        if (_SpellBook.find(aspell->getName()) == _SpellBook.end())
            _SpellBook[aspell->getName()] = aspell->clone();
}
void Warlock::forgetSpell(std::string name)
{
    if (_SpellBook.find(name) != _SpellBook.end())
    {
        _SpellBook.erase(_SpellBook.find(name));
    }
}
void Warlock::launchSpell(std::string name, ATarget &atarget)
{
    if (_SpellBook.find(name) != _SpellBook.end())
    {
    std::cout << "fuck\n";
        _SpellBook[name]->launch(atarget);
    }
}