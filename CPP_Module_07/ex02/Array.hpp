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
        std::cout << "unsigned\n";
        this->arr = new T[len];
        this->_len = len;
        for (unsigned int i = 0; i < len; i++)
        {
            arr[i] = 0;
        }
    }

    Array(int len)
    {
        (void) len;
        std::cout << "Please enter the data type of unsigned int.\n"; 
        std::cout << "arr is initialized to NULL and len is initialized to 0.\n";
        this->arr = NULL;
        this->_len = 0;
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
        std::cout << "awd\n";
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

    T& operator[] (int index)
    {
        //         std::cout << "_len : " << _len << "\n";
        std::cout << "index : " << index << "\n"; 
        //if (index >= this->_len)
            throw std::out_of_range("index is out of bounds");
        //return this->arr[index];
    };

    T& operator[] (unsigned int index)
    {
        //         std::cout << "_len : " << _len << "\n";
        std::cout << "index : " << index << "\n"; 
        if (index >= this->_len)
            throw std::out_of_range("index is out of bounds");
        return this->arr[index];
    };

    const T& operator[] (unsigned int index) const
    {
        //std::cout << "_len : " << _len << "\n";
        std::cout << "index : " << index << "\n"; 
        if (index >= this->_len)
            throw std::out_of_range("index is out of bounds\n");
        return this->arr[index];
    };

    void ShowAllData(const Array& ref) const
    { 
        for(unsigned int idx=0; idx<_len; idx++)
            std::cout<<ref[idx]<< std::endl; //컴파일 에러 발생
    }

    int *getArray(void)
    {
        return this->arr;
    }

    unsigned int *getArrayunsigined(void)
    {
        return this->arr;
    }
    
    unsigned int size(void) const
    {
        return this->_len;
    };
};

#endif