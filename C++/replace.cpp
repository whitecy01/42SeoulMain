#include <iostream>
#include <string>

int main() {
    std::string str = "Hello, world!";
    std::cout << "Original string: " << str << std::endl;

    str.replace(7, 5, "there");
    std::cout << "Modified string: " << str << std::endl;

    return 0;
}
