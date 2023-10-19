#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <deque>
# include <vector>
# include <ctime>
# include <iostream>
# include <string>
# include <iomanip>

class PmergeMe {
private:
    std::deque<int> deque;
    std::vector<int> vector;
    int size;
public:
    PmergeMe(void);
    PmergeMe(PmergeMe const &pmergeMe);
    ~PmergeMe();
    PmergeMe& operator=(PmergeMe const &pmergeMe);

    void insertArgs(char **argv);

    void insertVec(int p, int q);
    void mergeVec(int p, int q, int r);
    void sortVec(int p, int r);

    void insertDeque(int p, int q);
    void mergeDeque(int p, int q, int r);
    void sortDeque(int p, int r);

    void showResult(char **argv);
    void showNums(void);
    void handleError(std::string message);
};

#endif
