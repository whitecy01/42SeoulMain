#include "Convert.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
        std::cout << "Wrong Arguments\n";
    else
    {
        Convert convert(argv[1]);
        convert.convertAll();
    } 
}