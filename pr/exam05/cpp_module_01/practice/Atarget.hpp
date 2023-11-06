#ifndef ATARGET_HPP
#define ATARGET_HPP

#include <iostream>

#include "ASpell.hpp"

class ASpell;

class ATarget
{
    private:
        std::string type;
    public:
        std::string const &getType() const;
        virtual ATarget *clone() const = 0;
        ATarget(std::string type);
        virtual ~ATarget();

        ATarget(ATarget const &atarget);
        ATarget &operator=(ATarget const &atarget);

        void getHitBySpell(ASpell const &aspell) const;
};

#endif