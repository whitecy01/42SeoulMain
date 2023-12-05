// #include <iostream>
// int main()
// {
//     std::string str;
//     getline(std::cin, str);
//     int number = str.stoi();
//     std::cout << number;
// }

#include <iostream>
#include <string>

int main() 
{
    std::string numStr = "12345";
    int num = std::stoi(numStr);
    std::cout << "Converted integer: " << num << std::endl;
    return 0;
}
