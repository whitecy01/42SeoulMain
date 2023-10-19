#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cout << "Error: Not Enough Arguments\n";
        return 1;
    }
    PmergeMe pm;
    pm.showResult(argv);
    return 0;
}