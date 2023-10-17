#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Wrong argument!";
        return 1;
    }

    BitcoinExchange bitcoinExchange("data.csv");
    //bitcoinExchange.calcBitcoin(argv[1]);
    return 0;
}