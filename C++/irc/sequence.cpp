#include <iostream>

int main()
{
    std::string a = "\r";

    if (a[0] == '\r')
        std::cout << "fuck\n";
}