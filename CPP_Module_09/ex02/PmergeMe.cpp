#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{ 
	this->size = 0;
}

PmergeMe::~PmergeMe(){ }

PmergeMe::PmergeMe(PmergeMe const &pmergeme)
{
	*this = pmergeme;
}

PmergeMe& PmergeMe::operator=(PmergeMe const &pmergeme)
{
	if (this == &pmergeme)
		return *this;
	this->vector = pmergeme.vector;
	this->list = pmergeme.list;
	return *this;
}

void PmergeMe::parsing_sort(char **argv, int argc)
{
	if (argc < 2)
		handleError("Error: Not Enough Arguments");
    int i = 0;
    long num;

    while (argv[++i] != NULL)
	{
        num = std::atol(argv[i]);
        if (num < 0)
            handleError("Error: cannot insert negative number");
        else if (num == 0)
            handleError("Error: Wrong Arguments");
        else if (num > INT_MAX)
            handleError("Error: too big number");
		vector.push_back(num);
		list.push_back(num);
    }
	// for (std::vector<int>::iterator iter = vector.begin(); iter != vector.end(); iter++)
	// {
	// 	std::cout << *iter << "\n";
	// }

	size = i - 1;
	//벡터 정렬
	vector_sort(vector, 0, vector.size() - 1);
}


// left 0 right 5
void PmergeMe::vector_sort(std::vector<int> &vector, int left, int right)
{
	if (left < right)
	{
		std::cout << "left : " << left << " right : " << right << std::endl;
		int mid = left + (right - left) / 2;
		vector_sort(vector, left, mid);
		vector_sort(vector, mid + 1, right);

		//merge();
	}
}

void PmergeMe::handleError(std::string message) {
    std::cerr << message << "\n";
    std::exit(1);
}

