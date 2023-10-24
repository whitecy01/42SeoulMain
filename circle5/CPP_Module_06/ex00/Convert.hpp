#ifndef CONVERT_HPP
#define CONVERT_HPP

#include <iostream>
#include <limits.h>
#include <cstdlib>

class Convert {
private:
    std::string value;
    double doubleValue;
    char *endptr;
public:
    Convert();
    Convert(std::string value);
    Convert(Convert const &convert);
    ~Convert();
    Convert& operator=(Convert const &convert);

    void charConvert() const;
    void intConvert() const;
    void floatConvert() const;
    void doubleConvert() const;
    void convertAll() const;

   // bool checkValid(std::string value) const;
    bool checkInfo() const;

    std::string getValue(void) const;
    double getDoubleValue(void) const;
    char *getEndPtr(void) const;
};

#endif