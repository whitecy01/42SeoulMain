#include "SpellBook.hpp"


SpellBook::SpellBook()
{

}

SpellBook::~SpellBook()
{
    std::map<std::string, ASpell *>::iterator iter = _SpellBook.begin();

            for ( ; iter != _SpellBook.end(); iter++)
            {
                delete iter->second;
              
            }


    // for (std::map<std::string, ASpell*>::iterator it = _SpellBook.begin(); it != _SpellBook.end(); ++it) {
	// 	delete it->second;
	// }
	//_SpellBook.clear();
}

SpellBook::SpellBook(SpellBook const &spellbook)
{
    *this = spellbook;
}

SpellBook &SpellBook::operator=(SpellBook const &spellbook)
{
    if (this == &spellbook)
        return *this;
    _SpellBook = spellbook._SpellBook;
    return *this;
}

void SpellBook::learnSpell(ASpell *aspell)
{
    if (aspell)
    {
        _SpellBook[aspell->getName()] = aspell->clone();
    }
}
void SpellBook::forgetSpell(std::string const &name)
{
    if (_SpellBook.find(name) != _SpellBook.end())
    {
        std::map<std::string, ASpell *>::iterator iter = _SpellBook.find(name);
        delete iter->second;
        _SpellBook.erase(iter);
    }
}


ASpell* SpellBook::createSpell(std::string const &name)
{
    ASpell *tmp = NULL;
    if (_SpellBook.find(name) != _SpellBook.end())
    {
        tmp = _SpellBook[name];
    }
    return tmp;
}