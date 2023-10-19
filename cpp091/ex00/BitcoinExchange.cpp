#include "BitcoinExchange.hpp"

// if no data comes in, just say something
BitcoinExchange::BitcoinExchange(void)
{
    first = "0000-01-01";
    last = "9999-12-31";
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &bitcoinExchange)
{
    this->coinMap = bitcoinExchange.coinMap;
    this->first = bitcoinExchange.first;
    this->last = bitcoinExchange.last;
}

BitcoinExchange::~BitcoinExchange() { }

BitcoinExchange& BitcoinExchange::operator=(BitcoinExchange const &bitcoinExchange) {
    if (this != &bitcoinExchange) {
        this->coinMap = bitcoinExchange.coinMap;
        this->first = bitcoinExchange.first;
        this->last = bitcoinExchange.last;
    }
    return (*this);
}

// if char data comes in, save as map
BitcoinExchange::BitcoinExchange(const char *data)
{
    std::ifstream ifs;

    ifs.open(data, std::ios::in);
    if (!ifs.is_open())
        showErrorExit("Error! cannot open file!");

    // similar as get_next_line
    std::string line;
    getline(ifs, line); // first line is just title
    char *pos = NULL;
    while (getline(ifs, line))
    {
        if (line.size() < 10 || !isValidDate(line.substr(0, 10)))
            showErrorExit("Error: Invalid Date in csv file");
        if (!isValidValue(line.substr(11)))
            showErrorExit("Error: Invalid value in csv file");
        if (line.size() < 12 || std::strtof(line.substr(11).c_str(), &pos) < 0)
            showErrorExit("Error: Negative number in csv file");
        if (line[10] != ',')
            showErrorExit("Error: Invalid format in csv file");
        fillCoinMap(line.substr(0, 10), std::strtof(line.substr(11).c_str(), &pos));
    }
    if (coinMap.empty())
        showErrorExit("Error: map is Empty");
    this->first = coinMap.begin()->first;
    this->last = coinMap.rbegin()->first;
}

bool BitcoinExchange::isValidDate(std::string date)
{
    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());
    
    // check form
    if (date[4] != '-' || date[7] != '-')
        return false;
    for (size_t i = 0; i < date.length(); i++)
    {
        if (i == 4 || i == 7)
            continue;
        if (date[i] < '0' || date[i] > '9')
            return false;
    }

    // check year
    if (year < 1)
        return false;

    // check month
    if (month > 12 || month < 1)
        return false;
    
    // check day
    if (day < 1 || day > 31)
        return false;
    if (month == 2)
    {
        // check yunnyun
        if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        {
            if (day > 29)
                return false;
        }
        else
        {
            if (day > 28)
                return false;
        }
    }
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return false;
    return true;
}

bool BitcoinExchange::isValidValue(std::string value)
{
    int point = 0;
    int index = 0;

    if (value.empty())
        return false;
    if (value[0] == '-' || value[0] == '+')
        index++;
    while (value[++index] != '\0')
    {
        if (point > 1)
            return false;
        if (value[index] < '0' || value[index] > '9')
        {
            if (value[index] == '.')
                point++;
            else
                return false;
        }
    }
    return true;
}

void BitcoinExchange::showErrorExit(std::string message)
{
    std::cerr << message << "\n";
    std::exit(1);
}

void BitcoinExchange::showErrorContinue(std::string message)
{
    std::cerr << message << "\n";
}


void BitcoinExchange::fillCoinMap(std::string date, float value)
{
    if (coinMap.find(date) == coinMap.end())
        coinMap[date] = value;
    else
        showErrorExit("Error: Already exists in map\n");
}

void BitcoinExchange::calcBitcoin(const char *data)
{
    std::ifstream ifs;

    ifs.open(data, std::ios::in);
    if (!ifs.is_open())
        showErrorExit("Error! cannot open file!");

    std::string line;
    getline(ifs, line);
    while (getline(ifs, line))
    {
        if (line.empty())
            continue;
        if (!handleError(line))
            continue;
        findDate(line.substr(0, 10), std::atof(line.substr(13).c_str()));
    }
}

bool BitcoinExchange::handleError(std::string line)
{
    if (line.length() < 10)
    {
        showErrorContinue("Error: bad input => " + line);
        return false;
    }
    if (!isValidDate(line.substr(0, 10)) || line.substr(10, 3) != " | ")
    {
        showErrorContinue("Error: bad input => " + line);
        return false;
    }
    if (line.substr(0, 10) < first || line.substr(0, 10) > last)
    {
        showErrorContinue("Error: Date out of range");
        return false;
    }
    if (line.size() < 14 || !isValidValue(line.substr(13)))
    {
        showErrorContinue("Error: Invalid number => " + line.substr(13));
        return false;
    }
    else if (atof(line.substr(13).c_str()) < 0)
    {
        showErrorContinue("Error: not a positive number");
        return false;
    }
    else if (atol(line.substr(13).c_str()) > 1000)
    {
        showErrorContinue("Error: too large a number");
        return false;
    }
    return true;
}

void BitcoinExchange::findDate(std::string date, float value)
{
    std::map<std::string, float>::iterator iter = coinMap.upper_bound(date);
    iter--;
    printResult(iter, date, value);
}

void BitcoinExchange::printResult(std::map<std::string, float>::iterator iter, std::string date, float value)
{
    std::cout << date << " => " << value << " = " << iter->second * value << "\n";
}