#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void) {
}

PmergeMe::~PmergeMe(void) {
}

PmergeMe::PmergeMe(PmergeMe const &pmergeMe) {
    this->deque = pmergeMe.deque;
    this->vector = pmergeMe.vector;
    this->size = pmergeMe.size;
}

PmergeMe& PmergeMe::operator=(PmergeMe const &pmergeMe) {
    if (this != &pmergeMe) {
        this->deque = pmergeMe.deque;
        this->vector = pmergeMe.vector;
        this->size = pmergeMe.size;
    }
    return (*this);
}

void PmergeMe::insertArgs(char **argv) {
    int i = 0;
    long num;

    while (argv[++i] != NULL) {
        num = std::atol(argv[i]);
        if (num < 0)
            handleError("Error: cannot insert negative number");
        else if (num == 0)
            handleError("Error: Wrong Arguments");
        else if (num > INT_MAX)
            handleError("Error: too big number");
		vector.push_back(num);
		deque.push_back(num);
    }
    size = i - 1;
}

/* vector 정렬 시작 */
void PmergeMe::insertVec(int p, int q)
{
	for (int i = p; i < q; i++)
	{
		int j = i + 1;
		int tempVal = vector[j];
		while (j > p && vector[j - 1] > tempVal)
		{
			vector[j] = vector[j - 1];
			j--;
		}
		vector[j] = tempVal;
	}
}

void PmergeMe::mergeVec(int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;
	std::vector<int> LA;
	for (int i = p; i < q + 1; i++)
		LA.push_back(vector[i]);
	std::vector<int> RA;
	for (int i = q + 1; i < r + 1; i++)
		RA.push_back(vector[i]);
	int RIDX = 0;
	int LIDX = 0;
	for (int i = p; i < r - p + 1; i++)
	{
		if (RIDX == n2)
		{
			vector[i] = LA[LIDX];
			LIDX++;
		}
		else if (LIDX == n1)
		{
			vector[i] = RA[RIDX];
			RIDX++;
		}
		else if (RA[RIDX] > LA[LIDX])
		{
			vector[i] = LA[LIDX];
			LIDX++;
		}
		else
		{
			vector[i] = RA[RIDX];
			RIDX++;
		}
	}
}

void PmergeMe::sortVec(int p, int r)
{
	if (r - p > (int)vector.size() / 2)
	{
		int q = (p + r) / 2;
		sortVec(p, q);
		sortVec(q + 1, r);
		mergeVec(p, q, r);
	}
	else
		insertVec(p, r);
}
/* vector 정렬 끝 */

/* deque 정렬 시작 */
void PmergeMe::insertDeque(int p, int q)
{
	for (int i = p; i < q; i++)
	{
		int j = i + 1;
		int tempVal = deque[j];
		while (j > p && deque[j - 1] > tempVal)
		{
			deque[j] =  deque[j - 1];
			j--;
		}
		deque[j] = tempVal;
	}
}

void PmergeMe::mergeDeque(int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;
	std::deque<int> LA;
	for (int i = p; i < q + 1; i++)
		LA.push_back(deque[i]);
	std::deque<int> RA;
	for (int i = q + 1; i < r + 1; i++)
		RA.push_back(deque[i]);
	int RIDX = 0;
	int LIDX = 0;
	for (int i = p; i < r - p + 1; i++)
	{
		if (RIDX == n2)
		{
			deque[i] = LA[LIDX];
			LIDX++;
		}
		else if (LIDX == n1)
		{
			deque[i] = RA[RIDX];
			RIDX++;
		}
		else if (RA[RIDX] > LA[LIDX])
		{
			deque[i] = LA[LIDX];
			LIDX++;
		}
		else
		{
			deque[i] = RA[RIDX];
			RIDX++;
		}
	}
}

void PmergeMe::sortDeque(int p, int r)
{
	if (r - p > (int)deque.size() / 2)
	{
		int q = (p + r) / 2;
		sortDeque(p, q);
		sortDeque(q + 1, r);
		mergeDeque(p, q, r);
	}
	else
		insertDeque(p, r);
}
/* deque 정렬 끝 */

void PmergeMe::showResult(char **argv) {
    clock_t start;
    clock_t end;
    double duration;

    insertArgs(argv);
    std::cout << "Before:\t";
    showNums();

    start = clock();
    // 벡터 정렬
    sortVec(0, vector.size() - 1);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;

    std::cout << "After:\t";
    showNums();

    std::cout << "Time to process a range of " << std::setw(4) << size;
    std::cout.precision(6);
    std::cout << " elements with std::vector<int> : " << std::fixed << duration << " us" << "\n";
    
    start = clock();
    // 데크 정렬
    sortDeque(0, deque.size() - 1);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << "Time to process a range of " << std::setw(4) << size;
    std::cout << " elements with std::deque<int> : " << duration << " ms" << "\n";
}

void PmergeMe::showNums(void) {
    std::vector<int>::iterator iter = vector.begin();

    while (iter != vector.end()) {
        std::cout << *iter << " ";
        iter++;
    }
    std::cout << "\n";
}

void PmergeMe::handleError(std::string message) {
    std::cerr << message << "\n";
    std::exit(1);
}
