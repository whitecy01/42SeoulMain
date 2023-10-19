#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

# include <iostream>
# include <map>
# include <fstream>
# include <cstdlib>


class BitcoinExchange
{
private:
	std::map < std::string , float> coinMap;
	std::string first;
	std::string last;
public:
	BitcoinExchange();
	~BitcoinExchange();
	BitcoinExchange(BitcoinExchange const &bitcoinexchange);
	BitcoinExchange &operator=(BitcoinExchange const &bitcoinexchange);

	/* data.csv */
	BitcoinExchange(const char *data);
	int csv_line_check(std::string line);
	int isValidDate(std::string date);
	int isValidValue(std::string value);

	/* showError*/
	void showErrorMessage(std::string message);

	void fillCoinMap(std::string date, float value);


	// 모든 출력
	void outputelement();

	/* calcBitcoin*/
	void calcBitcoin(const char *argv);
	void findDate(std::string line, float value);
	int handleError(std::string line);
	void printResult(std::map<std::string, float>::iterator iter, std::string date, float value);
	void showErrorContinue(std::string message);
};

#endif