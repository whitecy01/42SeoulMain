#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <string>
# include <cstdlib>
# include <stdexcept>
s
# include <map>

class BitcoinExchange
{
private:
    std::map<std::string, float> coinMap;
    std::string first;
    std::string last;
public:
    BitcoinExchange(void);
    BitcoinExchange(const char *data);
    BitcoinExchange(BitcoinExchange const &bitcoinExchange);
    ~BitcoinExchange(void);
    BitcoinExchange& operator=(BitcoinExchange const &bitcoinExchange);

    bool isValidDate(std::string date);
    bool isValidValue(std::string value);
    void showErrorExit(std::string message);
    void showErrorContinue(std::string message);
    void fillCoinMap(std::string date, float value);
    void calcBitcoin(const char *data);
    void findDate(std::string date, float value);
    bool handleError(std::string line);
    void printResult(std::map<std::string, float>::iterator iter, std::string date, float value);
};

#endif
