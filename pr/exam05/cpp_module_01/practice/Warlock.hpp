#ifndef WARLOCK_HPP
# define WARLOCK_HPP

#include <iostream>

#include <map>
#include <iterator>

#include "ASpell.hpp"
#include "ATarget.hpp"

class Warlock
{
    private:
        std::string name;
        std::string title;
        Warlock();
        Warlock(Warlock const &warlock);
        Warlock &operator=(Warlock const &warlock);
        std::map<std::string, ASpell *> _SpellBook;

    public:
        std::string const &getName() const;
        std::string const &getTitle() const;
        void setTitle(std::string const &title);
        ~Warlock();
        Warlock(std::string name, std::string title);
        void introduce() const;

        void learnSpell(ASpell *aspell);
        void forgetSpell(std::string name);
        void launchSpell(std::string name, ATarget &atarget);        
};

#endif