#include <iostream>

int main(int argc, char **argv)
{
	if (argc < 2)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *\n";
	else{
		for (int i = 1; i < argc; i++)
		{
			for(int j = 0; argv[i][j]; j++)
			{
				std::cout << (char)std::toupper(argv[i][j]);
			}
		}
		std::cout << "\n";
	}
}