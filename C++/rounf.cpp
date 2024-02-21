#include <iostream>
#include <cmath>

int main() {
    float num = 3.14;
    float roundedNum = round(num);

    std::cout << "Original number: " << num << std::endl;
    std::cout << "Rounded number: " << roundedNum << std::endl;

    return 0;
}