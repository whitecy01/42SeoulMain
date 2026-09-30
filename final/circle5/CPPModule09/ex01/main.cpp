#include "RPN.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "Error: argument not exists";
        return 1;
    }

    RPN rpn(argv[1]);
    std::cout << rpn.calcRpn() << "\n";
    return 0;
}