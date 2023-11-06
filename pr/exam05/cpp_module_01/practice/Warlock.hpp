#ifndef WARLOCK_HPP
# define WARLOCK_HPP


#include <iostream>
#include "ASpell.hpp"
#include <map>

class Warlock 
{
    private:
        std::string name;
        std::string title;
        Warlock();
        Warlock &operator=(const Warlock &warlock);
        Warlock(const Warlock &warlcok);
        std::map < std::string, ASpell * > _SpellBook;

        
    public:
        Warlock(std::string anme, std::string title);
        ~Warlock();
        std::string getName() const;
        std::string getTitle() const;
        void setTitle(std::string const &title);
        void introduce() const;

        void learnSpell(ASpell* spell);
		void launchSpell(std::string SpellName, ATarget & target);
        void forgetSpell(std::string SpellName);
};

#endif