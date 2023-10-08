#include <iostream>

int main()
{
    double a = 4444444.233333;

    std::cout << a << "\n";
    
    std::cout << static_cast<int>(a) << "\n";
    std::cout << static_cast<float>(a) << "\n";


    std::cout << "===================a=========================\n";
        double b = 444444;

    std::cout << "b : \n";
    
    std::cout << static_cast<int>(b) << "\n";
    std::cout << static_cast<float>(b) << "\n";
    
    std::cout << (b) << "\n";

          double c = 0;

          
    std::cout << "===================c=========================\n";

    std::cout << "c : \n";
    
    std::cout << static_cast<int>(c) << "\n";
    std::cout << static_cast<float>(c) << "\n";
    
    std::cout << (c) << "\n";


    std::cout << "===================d=========================\n";
              double d = 42.0f;

    std::cout << "d : \n";
    
    std::cout << static_cast<int>(d) << "\n";
    std::cout << static_cast<float>(d) << "\n";
    
    std::cout << (d) << "\n";

    
    std::cout << "===================e=========================\n";
              double e = 444444.22;

    std::cout << "e : \n";
    
    std::cout << static_cast<int>(e) << "\n";
    std::cout << static_cast<float>(e) << "\n";
    
    std::cout << (e) << "\n";


    std::cout << "===================f=========================\n";
              double f = 444444;

    std::cout << "f : \n";
    
    std::cout << static_cast<int>(f) << "\n";
    std::cout << static_cast<float>(f) << "\n";
    
    std::cout << (f) << "\n";

    
    std::cout << "===================g=========================\n";
              double g = 4.23;

    std::cout << "g : \n";
    
    std::cout << static_cast<int>(g) << "\n";
    std::cout << static_cast<float>(g) << "\n";
    
    std::cout << (g) << "\n";


    
}