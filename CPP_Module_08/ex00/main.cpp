#include "easyfind.hpp"

int main()
{
    std::cout << "==================== list ====================\n";
    try
    {
        std::list<int> listInt;
        for (int i = 0; i < 10; i++)
            listInt.push_back(i);
        std::list<int>::iterator iter;
        iter = easyfind(listInt, 3);
        iter = easyfind(listInt, 100);
    } catch (std::exception &e) 
    {
        std::cout << e.what() << "\n";
    }
    std::cout << "==================== vector ====================\n";
    try
    {
        std::vector<int> vector;
        for (int j = 0; j < 10; j++)
        {
            vector.push_back(j);
        }
        std::vector<int>::iterator iter2;
        iter2 = easyfind(vector, 3);
        iter2 = easyfind(vector, 100);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    
}