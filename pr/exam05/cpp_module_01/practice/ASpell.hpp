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
        ASpell(std::string name, std::string effects);
        virtual ~ASpell();

        ASpell(ASpell const &aspell);
        ASpell &operator=(ASpell const &aspell);

        void launch(ATarget const &atarget) const;
};

#endif