#include <iostream>
#include <cmath>
#include <stdint.h>
#include "Array.hpp"

#define MAX_VAL 750
int main()
{
    // Array<int> numbers(-1);
    // if (!numbers.getArray())
    // {
    //     std::cout << "Awd\n";
    //     return (1);
    // }
    
    // Array<unsigned int> numbers4(2);
    // Array<unsigned int> numbers2(static_cast<unsigned int>(2));
    // if (!numbers2.getArrayunsigined())
    // {
    //     std::cout << "Awd\n";
    //     return (1);
    // }

    // Array<int> numbers3(static_cast<unsigned int>(2));
    // int* mirror = new int[2];
    // srand(time(NULL));
    // for (int i = 0; i < -1; i++)
    // {
    //     const int value = rand();
    //     numbers[i] = value;
    //     mirror[i] = value;
    // }
    // std::cout << numbers[2] << "\n";
    // std::cout << mirror[2] << "\n";

    // {
    //     Array<int> numbers3(static_cast<unsigned int>(2));
    //     Array<int> tmp = numbers3;
    //     Array<int> test(tmp);

    // }

    // for (int i = 0; i < -1; i++)
    // {
    //     if (mirror[i] != numbers[i])
    //     {
    //         std::cerr << "didn't save the same value!!" << std::endl;
    //         return 1;
    //     }
    // }
   const Array<unsigned int> numbers((unsigned int)10);
   // Array<int> number3(15);


    try
    {
        //numbers[-2] = 0;
        std::cout << numbers[0] << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    // try
    // {
    //     //numbers[MAX_VAL] = 0;
    //     numbers[9] = 0;
    //     std::cout << numbers[9] << "\n";
    //    //numbers.ShowAllData(numbers);
    // }
    // catch(const std::exception& e)
    // {
    //     std::cerr << e.what() << '\n';
    // }

    // try
    // {
    //     for (int i = 0; i < MAX_VAL; i++)
    //     {
    //         numbers[i] = rand();
    //     }
    // }
    // catch(const std::exception& e)
    // {
    //     std::cerr << e.what() << '\n';
    // }
    
    //delete [] mirror;//
    return 0;
}