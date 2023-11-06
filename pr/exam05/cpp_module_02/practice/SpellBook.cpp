#include "SpellBook.hpp"

SpellBook::SpellBook()
{

}

SpellBook::~SpellBook()
{
    for (std::map<std::string, ASpell *>::iterator iter = _SpallBook.begin(); iter != _SpallBook.end(); ++iter)
    {
        delete iter->second;
    }
    _SpallBook.clear();
}

SpellBook::SpellBook(SpellBook const &spellbook)
{
    *this = spellbook;
}

SpellBook &SpellBook::operator=(SpellBook const &spellbook)
{
    if (this == &spellbook)
        return *this;
    _SpallBook = spellbook._SpallBook;
    return *this;
}

void SpellBook::learnSpell(ASpell* aspell)
{
    if (aspell)
        _SpallBook[aspell->getName()] = aspell->clone();
}

void SpellBook::forgetSpell(std::string const &name)
{
    std::map<std::string, ASpell *>::iterator iter = _SpallBook.find(name);
    if (iter != _SpallBook.end())
    {
        delete iter->second;
        _SpallBook.erase(iter);
    }
}

ASpell* SpellBook::createSpell(std::string const &name)
{
    ASpell *tmp = NULL;
    if (_SpallBook.find(name) != _SpallBook.end())
    {
        tmp = _SpallBook[name];
    }
    return tmp;
}