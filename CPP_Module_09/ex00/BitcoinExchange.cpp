#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() { }

BitcoinExchange::~BitcoinExchange() { }

BitcoinExchange::BitcoinExchange(BitcoinExchange const &bitcoinexchange)
{
	*this = bitcoinexchange;
}

BitcoinExchange & BitcoinExchange::operator=(BitcoinExchange const &bitcoinexchange)
{
	if (this == &bitcoinexchange)
		return *this;
	this->data = bitcoinexchange.data;	
	return *this;
}

void BitcoinExchange::showErrorMessage(std::string message)
{
	std::cout << message << std::endl;
	std::exit(1);
}

BitcoinExchange::BitcoinExchange(const char *data)
{
	std::ifstream file;

	file.open(data, std::ios::in);
	if (!file.is_open())
		showErrorMessage("Error: could not open file");
	
	/* data.csv 파일 읽기*/

	//첫 번째는 넘어가야함.
	std::string line;
	getline(file, line);

	/* 인자 파싱 하기 */
	// 기본 검사
	// 1. size가 12 미만으로 들어오는지
	// 2. 값 안에 이상하는 게 들어가는지
	// 3. ',' 기준으로 잘 들어오는지
	// 4. ',' 뒤에 값은 오는지

	//값 검사
	/* 1. 년, 월, 일 검사 */
		// 년 1000 ~ 9999까지 검사
		// 월 1 ~ 12까지 들어오는 거 검사
		// 일 -> 각 월 마다 1월에서 12월에서 30일 31일 잘 들어왔는지. 검사, 윤년 검사
	/* 2. 값어치 검사 */

	while (getline(file, line))
	{
		//기본 검사
		if(line.size() < 12 || csv_line_check(line))
			showErrorMessage("Error: Invalid Date in csv file");
	}
	
}

int BitcoinExchange(std::string line)
{
	int i = 0;

	while (line[i])
	{
		if (!(('0' <= line[i] && line[i] <= '9') || line[i] == '-'|| \
			line[i] == ',' || line == '.'))
			return 1;
		i++;
	}
	return 0;
}



