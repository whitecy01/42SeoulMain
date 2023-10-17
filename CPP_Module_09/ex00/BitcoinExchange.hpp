#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

# include <iostream>
# include <map>
# include <fstream>
# include <cstdlib>


class BitcoinExchange
{
private:
	std::map < std::string , float> data;
public:
	BitcoinExchange();
	~BitcoinExchange();
	BitcoinExchange(BitcoinExchange const &bitcoinexchange);
	BitcoinExchange &operator=(BitcoinExchange const &bitcoinexchange);

	/* data.csv */
	BitcoinExchange(const char *data);
	void csv_line_check(std::string line);
	
	/* showError*/
	void showErrorMessage(std::string message);
	
	

}

#endif