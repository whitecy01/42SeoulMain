#include "Harl.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (std::cout << "argc error" << std::endl, 0);
	else
	{
		Harl harl;

		harl.complain(argv[1]);
	}
}