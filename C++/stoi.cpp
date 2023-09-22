#include <iostream>
int main()
{
    std::string str;
    getline(std::cin, str);
    int number = str.stoi();
    std::cout << number;
}