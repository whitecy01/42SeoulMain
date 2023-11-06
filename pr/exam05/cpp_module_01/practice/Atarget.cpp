#include "ATarget.hpp"


ATarget::ATarget(std::string type) : type(type)
{

}

ATarget::~ATarget(){}

ATarget::ATarget(ATarget const &atarget)
{
    *this = atarget;
}

ATarget &ATarget::operator=(ATarget const &atarget)
{
    if (this == &atarget)
        return *this;
    type = atarget.type;
    return *this;
}

std::string const &ATarget::getType() const
{
    return this->type;
}


void ATarget::getHitBySpell(ASpell const &aspell) const
{
 std::cout << type << " has benn " << aspell.getEffects() << "!" << std::endl;
}