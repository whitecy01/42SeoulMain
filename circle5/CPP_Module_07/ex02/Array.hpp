#ifndef ARRAY_HPP
# define ARRAY_HPP

#include <iostream>

template<typename T>
class Array
{
private:
    T *arr;
    unsigned int _len;
public:
    Array(void)
    {
        this->arr = NULL;
        this->_len = 0;
    }

    Array(unsigned int len)
    {
        this->arr = new T[len];
        this->_len = len;
        for (unsigned int i = 0; i < len; i++)
        {
            arr[i] = 0;
        }
	}

    ~Array(void)
    {
        if (arr)
            delete [] this->arr;
    }

    Array(const Array &array)
    {
        this->arr = NULL;
        *this = array;
    }

    Array &operator=(const Array &array)
    {
        if (this == &array)
            return (*this);
        this->_len = array._len;
        if (this->arr)
            delete [] this->arr;
        this->arr = new T[array._len];
        for (unsigned int i = 0; i < array._len; i++)
        {
            this->arr[i] = array.arr[i];
        }
        return *this;
    }

    T& operator[] (unsigned int index)
    {
        if (index >= this->_len)
            throw std::out_of_range("index is out of bounds");
        return this->arr[index];
    };

    const T& operator[] (unsigned int index) const
    {
        if (index >= this->_len)
            throw std::out_of_range("index is out of bounds\n");
        return this->arr[index];
    };

    unsigned int size(void) const
    {
        return this->_len;
    };
};

#endif