#include "ASpell.hpp"


ASpell::ASpell(std::string name, std::string effects) : name(name), effects(effects)
{

}

ASpell::~ASpell(){}

ASpell::ASpell(ASpell const &aspell)
{
    *this = aspell;
}

ASpell &ASpell::operator=(ASpell const &aspell)
{
    if (this == &aspell)
        return *this;
    name = aspell.name;
    effects = aspell.effects;
    return *this;
}

std::string const &ASpell::getName() const
{
    return this->name;
}


std::string const &ASpell::getEffects() const
{
    return this->effects;
}

void ASpell::launch(ATarget const &atarget) const
{
    atarget.getHitBySpell(*this);
}