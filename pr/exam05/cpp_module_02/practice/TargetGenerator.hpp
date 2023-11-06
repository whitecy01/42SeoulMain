#ifndef TARGETGENERATOR_HPP
#define TARGETGENERATOR_HPP


#include <map>
#include <iterator>

#include "ATarget.hpp"

class TargetGenerator
{
    private:
        std::map<std::string, ATarget *> _TargetBook;
        TargetGenerator(TargetGenerator const &src);
        TargetGenerator &operator=(TargetGenerator const &src);
    public:
        TargetGenerator();
        ~TargetGenerator();

        void learnTargetType(ATarget*);
        void forgetTargetType(std::string const &);
        ATarget* createTarget(std::string const &);


};

#endif