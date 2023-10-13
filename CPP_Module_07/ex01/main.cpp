#include "iter.hpp"


int main(void) {
    int arrInt[5] = {1, 2, 3, 4, 5};
    iter(arrInt, 5, func);
    std::cout << "\n";

    char arrChar[5] = {'a', 'b', 'c', 'd', 'e'};
    iter(arrChar, 5, func);
    std::cout << "\n";

    std::string arrString[5] = {"Hi", "My", "name", "is", "jaeyojun"};
    iter(arrString, 5, func);
    std::cout << "\n";
    
    double arrDouble[5] = {0.1, 0.2, 0.3, 0.4, 0.5};
    iter(arrDouble, 5, func);

    return 0;
}