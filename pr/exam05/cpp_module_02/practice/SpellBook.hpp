#ifndef SPELLBOOK_HPP
#define SPELLBOOK_HPP


#include <map>
#include "ASpell.hpp"
#include <iterator>

class SpellBook
{
    private:
        std::map<std::string, ASpell *> _SpellBook;
        SpellBook(SpellBook const &spellbook);
        SpellBook &operator=(SpellBook const &spellbook);
    public:
        SpellBook();
        ~SpellBook();

        void learnSpell(ASpell*);
        void forgetSpell(std::string const &);
        ASpell* createSpell(std::string const &);


};

#endif