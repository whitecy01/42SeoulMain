#include "Convert.hpp"

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

bool Convert::checkValid(std::string value) const {
    if (value == "nan" || value == "-inf" || value == "+inf" || value == "inf") {
        return false;
    } else {
        return true;
    }
}

void Convert::charConvert(void) const
{
    std::cout << "char: ";
    if (!checkValid(this->value))
    {
        std::cout << "impossible\n";
    } else if (this->doubleValue < 33 || this->doubleValue > 128) {
        std::cout << "Non displayable\n";
    } else {
        std::cout << "'" << static_cast<char>(doubleValue) << "'\n";
    }
}


void Convert::intConvert(void) const
{
    std::cout << "int: ";
    if (!checkValid(this->value))
    {
        std::cout << "impossible\n";
    } else if (this->doubleValue < INT_MIN || this->doubleValue > INT_MAX) {
        std::cout << "impossible\n";
    } else {
        std::cout << static_cast<int>(doubleValue) << "\n";
    }
}

void Convert::floatConvert(void) const
{
    std::cout << "float: ";

    std::cout << doubleValue << "\n";
    
    std::cout << static_cast<int>(doubleValue) << "\n";
    std::cout << "value : " << value << "\n";
    if (!checkValid(this->value))
    {
        std::cout << this->value << "f\n";
    } 
    else if (static_cast<int>(doubleValue) == doubleValue) 
    {
        if (value.length() <= 6)
          std::cout << static_cast<float>(doubleValue) << ".0f\n";
        else
          std::cout << static_cast<float>(doubleValue) << "\n";
    } 
    else if(value.find(".") != std::string::npos)
    {//정수부가 6개 이상일 때 예외처리
        //int point = value.find(".");
        // if(value.length() <= 6)
        //     std::cout << static_cast<float>(doubleValue) << ".0f\n";
        // else if (point >= 7)
            std::cout << static_cast<float>(doubleValue) << "f\n";
        // else
        //     std::cout << static_cast<float>(doubleValue) << ".0f\n";
    } 
    else {
        std::cout << static_cast<float>(doubleValue) << ".0f\n";
    }
}

void Convert::doubleConvert(void) const
{
    std::cout << "double: ";
    if (!checkValid(this->value)) {
        std::cout << this->value << "\n";
    } else if (static_cast<int>(doubleValue) == doubleValue)
    {      
        if (value.length() <= 6)
          std::cout << doubleValue << ".0\n";
        else
          std::cout << static_cast<float>(doubleValue) << "\n";
        
    } else if (this->value.find(".") != std::string::npos) {
        std::cout << doubleValue << "\n";
    } else {
        std::cout << doubleValue << ".0\n";
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