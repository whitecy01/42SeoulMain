#include <iostream>
#include <fstream>

int main(int argc, char **argv)
{
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
	infile.close();
	outfile.close();
}