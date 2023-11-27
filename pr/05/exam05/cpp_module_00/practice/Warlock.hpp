#ifndef WARLOCK_HPP
# define WARLOCK_HPP


#include <iostream>

class Warlock 
{
    private:
        std::string name;
        std::string title;
        Warlock();
        Warlock &operator=(const Warlock &warlock);
        Warlock(const Warlock &warlcok);
    public:
        Warlock(std::string anme, std::string title);
        ~Warlock();
        std::string getName() const;
        std::string getTitle() const;
        void setTitle(std::string const &title);
        void introduce() const;

        
};

#endif