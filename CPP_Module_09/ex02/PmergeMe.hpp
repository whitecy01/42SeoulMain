#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <list>
# include <ctime>
# include <iomanip>
#include <iostream>
#include <iterator>
#include <cstdlib>


class PmergeMe 
{
private:
	/* vector */
	std::vector<int> vector;
	std::vector<int> mainchin;
	std::vector<int> pending;
	/* 결과물*/
	std::vector<int> res;

	int size;
	std::vector<int> jascbsthal;


	/* list */
	std::list<int> list;
	std::list<int> mainchin_list;
	std::list<int> pending_list;
	std::list<int> jascbsthal_list;
	std::list<int> res_list;

public:
	PmergeMe();
	~PmergeMe();
	PmergeMe(PmergeMe const &pmergeme);
	PmergeMe&operator=(PmergeMe const &pmergeme);

	void showNums_result_vector(void);

	void parsing_sort(char **argv, int argc);
	void handleError(std::string message);

	/* vector 정렬 */
	void vector_sort(std::vector<int> &vector);
	void calc_jascbsthal(std::vector<int> vector);
	void resFindPair(std::vector<std::vector<int> > &result);
	void sort_j(void);


	void binaryInsert(std::vector<int>& arr, int element) ;
	void binaryInsertionSort(int elemnt);

	/* list 정렬 */
	void list_sort(std::list<int> &list);
	void resFindPair_list(std::list<std::list<int> > &result);
	void sort_j_list(void);
	void binaryInsert_list(std::list<int>& arr, int element) ;
	void binaryInsertionSort_list(int elemnt);
	//void merge();
};

#endif