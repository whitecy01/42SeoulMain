#include "Convert.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
        std::cout << "Wrong Arguments\n";
    else
    {
		if (argv[1][0] == '\0')
		{
			std::cout << "Wrong Arguments\n";
			return (0);
		}
		Convert convert(argv[1]);
        convert.convertAll();
    } 
}