#ifndef WARLOCK_HPP
#define WARLOCK_HPP

#include <iostream>

class Warlock
{
    private: 
        std::string name;
        std::string title;
        Warlock();
        Warlock(Warlock const &warlock);
        Warlock &operator=(Warlock const &warlock);
    public:
        std::string const &getName() const;
        std::string const &getTitle() const;
        void setTitle(std::string const &title);
        Warlock(std::string name, std::string title);
        ~Warlock();
        void introduce() const;
};

#endif