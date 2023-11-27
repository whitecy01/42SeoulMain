#include "ATarget.hpp"

ATarget::ATarget(std::string type)
{
    this->type = type;
}

ATarget::~ATarget()
{

}

ATarget::ATarget(ATarget const &atarget)
{
    *this = atarget;
}

ATarget& ATarget::operator=(ATarget const &atarget)
{
    if(this == &atarget)
        return *this;
    this->type = atarget.getType();
    return *this;
}


std::string ATarget::getType() const 
{
    return this->type;
}

void ATarget::getHitBySpell(ASpell const &aspell) const 
{
    std::cout << this->type << " has been " << aspell.getEffects() << std::endl;  
}