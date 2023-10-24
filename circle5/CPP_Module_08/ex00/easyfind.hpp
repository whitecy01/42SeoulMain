#ifndef EASYFIND_HPP
# define EASYFIND_HPP

#include <list>
#include <algorithm>
#include <vector>
#include <iostream>

template<typename T>
typename T::iterator easyfind(T &container, int value)
{
    typename T::iterator iter;

    iter = std::find(container.begin(), container.end(), value);
    if (iter == container.end())
        throw std::runtime_error("fail to find value");
    std::cout << "success to find value\n";
    return iter;
}

#endif