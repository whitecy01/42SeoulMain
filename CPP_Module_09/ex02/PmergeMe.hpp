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
	std::vector<int> res;
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
	std::vector<int> mergeSort(const std::vector<int>& input);
	std::vector<int> merge(const std::vector<int>& left, const std::vector<int>& right);
	double calc_jascbsthal(size_t number, double Jacobsthal_number);
	
	void ford_John(std::vector<std::vector<int> > &result);
	//void merge();
};

#endif