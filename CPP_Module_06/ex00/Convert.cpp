#include "Convert.hpp"
#include <cmath>

Convert::Convert(void) : value("None"), doubleValue(0), endptr(NULL)
{

}

Convert::Convert(std::string value) : value(value)
{
    this->doubleValue = strtod(this->value.c_str(), &(this->endptr));
}

Convert::Convert(Convert const &convert)
{
    *this = convert;    
}

Convert::~Convert(void)
{

} 

Convert& Convert::operator=(Convert const &convert) 
{
    if (this == &convert)
        return *this;
    this->value = convert.getValue();
    this->doubleValue = convert.getDoubleValue();
    this->endptr = convert.getEndPtr();
    return *this;
}

void Convert::charConvert(void) const
{
    std::cout << "char: ";

	if(std::isnan(this->doubleValue) || std::isinf(this->doubleValue))
		std::cout << "impossible\n";
	else if (this->doubleValue <= 31 || this->doubleValue > 128)
	{
		if ((this->doubleValue >= 0 && this->doubleValue <= 31) || \
			this->doubleValue == 127)
			std::cout << "Non displayable\n";
		else
			std::cout << "impossible\n";
    }
	else
	{
        std::cout << "'" << static_cast<char>(doubleValue) << "'\n";
    }
}

void Convert::intConvert(void) const
{
    std::cout << "int: ";

	if(std::isnan(this->doubleValue) || std::isinf(this->doubleValue))
		std::cout << "impossible\n";
	else if (this->doubleValue < INT_MIN || this->doubleValue > INT_MAX) 
	{
		std::cout << "impossible\n";
	} 
	else 
	{
		std::cout << static_cast<int>(doubleValue) << "\n";
	}
}

void Convert::floatConvert(void) const
{
    std::cout << "float: ";

   	if(std::isnan(this->doubleValue) || std::isinf(this->doubleValue))
		std::cout << std::showpos << static_cast<float>(doubleValue) << "\n";
    else if (static_cast<int>(doubleValue) == doubleValue) 
	{
		if (value.length() <= 6)
          std::cout << static_cast<float>(doubleValue) << ".0f\n";
        else
          std::cout << static_cast<float>(doubleValue) << "f\n";
    } 
    else if(value.find(".") != std::string::npos)
    {
		std::cout << static_cast<float>(doubleValue) << "f\n";
    }
    else
	{
		std::cout << static_cast<float>(doubleValue) << "f\n";
    }
}

void Convert::doubleConvert(void) const
{
    std::cout << "double: ";

	if(std::isnan(this->doubleValue) || std::isinf(this->doubleValue))
		std::cout << std::showpos << static_cast<float>(doubleValue) << "\n";
	else if (static_cast<int>(doubleValue) == doubleValue)
    {      
        if (value.length() <= 6)
          std::cout << doubleValue << ".0\n";
        else
          std::cout << static_cast<float>(doubleValue) << "\n";
    } else if (this->value.find(".") != std::string::npos) {
        std::cout << doubleValue << "\n";
    } else {
        std::cout << doubleValue << "\n";
    }
}

bool Convert::checkInfo(void) const
{
    if (*(this->endptr) && !(*(this->endptr) == 'f'))
        return false;
    return true;
}

void Convert::convertAll(void) const
{
    if (!checkInfo())
        std::cout << "Wrong inputs\n";
    else
    {
        this->charConvert();
        this->intConvert();
        this->floatConvert();
        this->doubleConvert();
    }

}

std::string Convert::getValue(void) const
{
    return this->value;
}

double Convert::getDoubleValue(void) const
{
    return this->doubleValue;
}

char *Convert::getEndPtr(void) const
{
    return this->endptr;
}