#include <iostream>
#include <string.h>
int main()
{
    char *str;

    str = "awD12";

    for (int i = 0; i < strlen(str); i++)
    {
        std::cout << (char)std::toupper(str[i]);
    }
    std::cout << std::endl;
}