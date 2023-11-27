#include "ASpell.hpp"

ASpell::ASpell(std::string name, std::string effects)
{
    this->name = name;
    this->effects = effects;
}

ASpell::~ASpell()
{

}

ASpell::ASpell(ASpell const &aspell)
{
    *this = aspell;
}

ASpell &ASpell::operator=(ASpell const &aspell)
{
    if (this == &aspell)
        return *this;
    this->name = aspell.getName();
    this->effects = aspell.getEffects();
    return *this;
}

std::string ASpell::getName() const
{
    return this->name;
}

std::string ASpell::getEffects() const
{
    return this->effects;
}

void ASpell::launch(ATarget const &atarget) const 
{
    atarget.getHitBySpell(*this);
}