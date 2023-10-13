#ifndef WHATEVER_HPP
# define WHATEVER_HPP

#include <iostream>

template<typename T>
void iter(T *array, int len, void (*func)(T &))
{
	//음수 예외 처리 
	for (int i = 0; i < len; i++)
	{
		func(array[i]);
	}
	
}

template <typename T>
void func(T &data)
{
	std::cout << data << " ";
}
#endif