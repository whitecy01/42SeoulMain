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
	std::vector<int> res_copy;
	int size;
	//야콥스탈 수 넣어주가
	std::vector<int> jascbsthal;
	std::list<int> list;

public:
	PmergeMe();
	~PmergeMe();
	PmergeMe(PmergeMe const &pmergeme);
	PmergeMe&operator=(PmergeMe const &pmergeme);

	void parsing_sort(char **argv, int argc);
	void handleError(std::string message);

	/* vector 정렬 */
	void vector_sort(std::vector<int> &vector);
	std::vector<int> mergeSort(const std::vector<int>& input);
	std::vector<int> merge(const std::vector<int>& left, const std::vector<int>& right);
	void calc_jascbsthal(std::vector<int> vector);
	
	void ford_John(std::vector<std::vector<int> > &result);
	//void merge();
	std::vector<int> resFindPair(std::vector<std::vector<int> > &result);
	void sort_j(std::vector<int> &pend);
};

#endif