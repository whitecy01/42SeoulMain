

#include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator()
{

}

TargetGenerator::~TargetGenerator()
{

}

TargetGenerator::TargetGenerator(TargetGenerator const &src)
{
    *this = src;
}

TargetGenerator &TargetGenerator::operator=(TargetGenerator const &src)
{
    if (this == &src)
        return *this;
    _TargetBook = src._TargetBook;
    return *this;
}

void TargetGenerator::learnTargetType(ATarget* atarget)
{
    if (atarget)
        _TargetBook[atarget->getType()] = atarget;
}

void TargetGenerator::forgetTargetType(std::string const &name)
{
    //std::map<std::string, ATarget *>::iterator iter = _TargetBook.find(name);
    if (_TargetBook.find(name) != _TargetBook.end())
    {
        _TargetBook.erase(_TargetBook.find(name));
    }
}

ATarget* TargetGenerator::createTarget(std::string const &name)
{
    ATarget *tmp = NULL;
    if (_TargetBook.find(name) != _TargetBook.end())
    {
        tmp = _TargetBook[name];
    }
    return tmp;
}