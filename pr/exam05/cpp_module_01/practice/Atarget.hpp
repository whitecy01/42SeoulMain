#ifndef ATARGET_HPP
#define ATARGET_HPP

#include "ASpell.hpp"
#include <iostream>

class ASpell;

class ATarget
{
    protected:
        std::string type;
    public:
        std::string getType() const;
        virtual ATarget* clone() const = 0;
        ATarget(std::string type);
        virtual ~ATarget();
        ATarget( ATarget const &atarget);
        ATarget &operator=( ATarget const &atarget);
        void getHitBySpell(ASpell const &aspell) const;



};

#endif