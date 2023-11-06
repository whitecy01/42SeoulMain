#ifndef WARLOCK_HPP
#define WARLOCK_HPP

#include <iostream>

#include "ASpell.hpp"
#include <map>
#include <iterator>
#include "SpellBook.hpp"

class Warlock
{
    private: 
        std::string name;
        std::string title;
        Warlock();
        Warlock(Warlock const &warlock);
        Warlock &operator=(Warlock const &warlock);
        SpellBook _SpellBook;
    public:
        std::string const &getName() const;
        std::string const &getTitle() const;
        void setTitle(std::string const &title);
        Warlock(std::string name, std::string title);
        ~Warlock();
        void introduce() const;

        void learnSpell(ASpell *aspell);
        void forgetSpell(std::string name);
        void launchSpell(std::string name, ATarget &atarget);
};

#endif