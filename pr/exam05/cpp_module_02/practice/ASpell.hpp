#ifndef ASPELL_HPP
#define ASPELL_HPP

#include <iostream>

#include "ATarget.hpp"

class ATarget;

class ASpell
{
    private:
        std::string name;
        std::string effects;

    public:
        std::string const &getName() const;
        std::string const &getEffects() const;
        virtual ASpell *clone() const = 0;
        virtual ~ASpell();

        ASpell(std::string name, std::string effects);
        ASpell();
        ASpell &operator=(ASpell const &aspell);
        ASpell(ASpell const &aspell);

        void launch(ATarget const &atarget) const;

};

#endif