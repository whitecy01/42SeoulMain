#include <iostream>

int main()
{
	float result = 0.0;
	int i = 0;

	for (i = 0 ; i< 100; i++)
	{//std::cout << result << "\n";
		result += 0.1;
	}
	if (result == 10)
		std::cout << result << "\n";
}