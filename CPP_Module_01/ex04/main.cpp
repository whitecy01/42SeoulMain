#include <iostream>
#include <fstream>

int main(int argc, char **argv)
{
	if (argc != 4)
		return (std::cout << "argc is not four" << std::endl, 0);
	std::string s1 = argv[2];
	std::string s2 = argv[3];
	std::string inFileName = argv[1];
	std::string outFileName = inFileName + ".replace";
	int len1 = s1.length();
	int len2 = s2.length();
	if (inFileName.length() == 0 || len1 == 0 || len2 == 0)
		return (std::cout << "Arguments length is 0\n",	0);
	std::ifstream infile;
	infile.open(inFileName.c_str());
	std::ofstream outfile;
	outfile.open(outFileName.c_str());
	if (infile.fail() || outfile.fail())
		return (std::cout << "Open Failed\n", 0);

	std::string line;
	while (true)
	{
		std::getline(infile, line);
		
		size_t pos = 0;
		while (true)
		{
			pos = line.find(s1, pos);
			if (pos == std::string::npos)
				break ;
			line.erase(pos, len1);
			line.insert(pos, s2);
			pos += len2;
		}
		outfile << line;
		if (infile.fail())
			break ;
		outfile << std::endl;	
	}
	infile.close();
	outfile.close();
}