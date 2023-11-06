#ifndef ASPEEL_HPP
# define ASPEEL_HPP

#include <iostream>
#include "ATarget.hpp"

class ATarget;

class ASpell 
{
    protected:
        std::string name;
        std::string effects;
    public:
        std::string getName() const;
        std::string getEffects() const;
        virtual ASpell* clone() const = 0;
        ASpell(std::string name, std::string effects);
        ASpell( ASpell const &aspell);
        ASpell &operator=( ASpell const &aspell);
        virtual ~ASpell();
        void launch(ATarget const &atarget) const ;
};

#endif