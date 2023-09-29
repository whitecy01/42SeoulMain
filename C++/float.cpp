#include <iostream>

int main()
{
	int a = 0;
	++a;
	std::cout << (float)a / (1 << 8) << std::endl;
}