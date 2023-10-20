#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <list>
#include <iostream>
#include <cstdlib>

class PmergeMe 
{
private:
	std::vector<int> vector;
	std::list<int> list;
	int size;
public:
	PmergeMe();
	~PmergeMe();
	PmergeMe(PmergeMe const &pmergeme);
	PmergeMe&operator=(PmergeMe const &pmergeme);

	void parsing_sort(char **argv, int argc);
	void handleError(std::string message);

	/* vector 정렬 */
	void vector_sort(std::vector<int> &vector, int left, int right);
	
	//void merge();
};

#endif