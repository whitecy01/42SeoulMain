#include <iostream>
#include <string>

int ft_atoi(char *tmp)
{

	int count = strlen(tmp);
	if (tmp[0] == '0' )
		throw(0);
	
	int i = 0;
	int num = 0;
	while (tmp[i])
	{
		if (('0' > tmp[i] && tmp[i] > '9'))
			throw(tmp[i]);
		num += (int)(pow((double)10, (count - 1) - i * tmp[i] - '0'));
		i++;
	}
	return num;
}


int main()
{
	char num1[100], num2[100];

	std::cin >> num1 >> num2;

	try
	{
		std::cout << num1 << " + " << num2 << ft_atoi(num1) + ft_atoi(num2) << "\n"; 
	}
	catch(int num2)
	{
		if (!num2)
			std::cout << "0으로 시작될 수 없다\n";
	}
	catch(char number)
	{
		std::cout << "숫자가 아니다.\n";
	}
	
}