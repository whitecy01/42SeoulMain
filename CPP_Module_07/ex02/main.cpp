#include <iostream>
#include <cmath>
#include <stdint.h>
#include "Array.hpp"

#define MAX_VAL 750

int main()
{
    Array<int> numbers1(-1);

    Array<int> numbers(static_cast<unsigned int>(MAX_VAL));
    int* mirror = new int[MAX_VAL];
    srand(time(NULL));
    for (int i = 0; i < MAX_VAL; i++)
    {
        const int value = rand();
        numbers[i] = value;
        mirror[i] = value;
    }

    {
        Array<int> tmp = numbers;
        Array<int> test(tmp);
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        if (mirror[i] != numbers[i])
        {
            std::cout << "didn't save the same value!!" << std::endl;
            return 1;
        }
    }

	Array<int> exam(numbers);
	std::cout << exam[2] << std::endl;

    try
    {
        numbers[-2] = 0;
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
	try
    {
        numbers[MAX_VAL] = 0;
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }

    delete [] mirror;
    return 0;
}