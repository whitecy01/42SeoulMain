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
        virtual ~ATarget();
        
        ATarget(std::string type);
        ATarget();
        ATarget &operator=(ATarget const &atarget);
        ATarget(ATarget const &atarget);

        void getHitBySpell(ASpell const &aspell) const;

};

#endif