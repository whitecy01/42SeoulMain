 #include "TargetGenerator.hpp"


TargetGenerator::TargetGenerator()
{

}

TargetGenerator::~TargetGenerator()
{

    //  std::map<std::string, ATarget *>::iterator iter = _TargetBook.begin();
    // if (iter->second != NULL)
    // {
    //     for ( ; iter != _TargetBook.end(); iter++)
    //     {
    //         std::exit(1);
    //         if (iter->second != NULL)
    //         {
    //             delete iter->second;
    //             _TargetBook.erase(iter->first);
    //         }
    //     }
    // }
    
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