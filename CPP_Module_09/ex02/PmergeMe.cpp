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
		this->vector.push_back(num);
		this->list.push_back(num);
    }
	size = i - 1;

	if (this->vector.size() == 1 && this->list.size() == 1)
	{
		this->res.push_back(vector[0]);
		this->res_list.push_back(*this->list.begin());
	}

    clock_t start;
    clock_t end;
    double duration;

    std::cout << "Before_vector:\t";
    std::vector<int>::iterator iter = this->vector.begin();

    while (iter != this->vector.end()) {
        std::cout << *iter << " ";
        iter++;
    }
    std::cout << "\n";

	calc_jascbsthal(this->vector);

	start = clock();
	vector_sort(this->vector);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;

	
	std::cout << "After_vector:\t";
    showNums_result_vector();

	std::cout << "Time to process a range of " << std::setw(4) << size;
    std::cout.precision(6);
    std::cout << " elements with std::vector<int> : " << std::fixed << duration << " us" << "\n";
    

	std::cout << "Before_list:\t";
	for (std::list<int>::iterator it = this->list.begin(); it != this->list.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	start = clock();
	list_sort(this->list);
	end = clock();
    
	std::cout << "After_list:\t";
	for (std::list<int>::iterator it = this->res_list.begin(); it != this->res_list.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	duration = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << "Time to process a range of " << std::setw(4) << size;
    std::cout << " elements with std::list<int> : " << duration << " ms" << "\n";

	// std::cout << "res_vector: ";
	// for (std::vector<int>::iterator it = this->res.begin(); it != this->res.end(); ++it)
	// {
	// 	std::cout << *it << " ";
	// }
	// std::cout << std::endl;


	std::vector<int>::iterator it1 = this->res.begin();
	int tmp1 = *it1;
	if (this->res.size() != this->list.size())
	{
		std::cout << "size error" << std::endl;
		std::cout << this->res.size() << ' ' << this->list.size() << std::endl;
	}
	for (std::vector<int>::iterator it1 = this->res.begin(); it1 != this->res.end(); ++it1)
	{
		if (tmp1 > *it1)
		{
			std::cout << "error: " << *it1 << ' ' << *(--it1) << ' ' << tmp1 << ' ' << *it1 << std::endl;
			return;
		}
		tmp1 = *it1;
	}


	std::list<int>::iterator it = this->res_list.begin();
	int tmp = *it;
	if (this->res_list.size() != this->list.size())
	{
		std::cout << "size error" << std::endl;
		std::cout << this->res_list.size() << ' ' << this->list.size() << std::endl;
	}
	for (std::list<int>::iterator it = this->res_list.begin(); it != this->res_list.end(); ++it)
	{
		if (tmp > *it)
		{
			std::cout << "error: " << *it << ' ' << *(--it) << ' ' << tmp << ' ' << *it << std::endl;
			return;
		}
		tmp = *it;
	}

}


void PmergeMe::showNums_result_vector(void)
{
    std::vector<int>::iterator iter = this->res.begin();

    while (iter != this->res.end()) {
        std::cout << *iter << " ";
        iter++;
    }
    std::cout << "\n";
}

void PmergeMe::list_sort(std::list<int> &list)
{
	std::list<std::list<int> > result;

    if (list.size() == 1)
		return;
	//1. 인자값을 반으로 나눈 다음에 중간을 통해 큰 거 앞으로 작은 거 뒤로
	unsigned int behind;
	behind = list.size() / 2;
	for (unsigned int i = 0; i < list.size() / 2; i++)
	{
		std::list<int>::iterator iter = list.begin();
		std::list<int>::iterator iter2 = list.begin();
		std::advance(iter, i);
		std::advance(iter2, behind);
		if (*iter < *iter2 )
		{
			std::swap(*iter , *iter2 );
		}
		behind++;
	}

	// //2. 정렬된 친구들 벡터 안에 벡터로 묶어주기
	if (list.size() % 2 == 0)
	{
		unsigned int behind;
		behind = list.size() / 2;
		for (  unsigned int i = 0; i < list.size() / 2; i++)
		{
			std::list<int>::iterator iter = list.begin();
			std::list<int>::iterator iter2 = list.begin();
			std::advance(iter, i);
			std::advance(iter2, behind);

			std::list<int> pair;
			if (*iter)
				pair.push_back(*iter);
			else
				pair.push_back(0);
			if (*iter2)
			{
				pair.push_back(*iter2);
				behind++;
			}
			else
				pair.push_back(0);

			result.push_back(pair);
		}
	}
	else
	{
		unsigned int behind;
		behind = list.size() / 2;
		for (unsigned int i = 0; i < list.size() / 2; i++)
		{
			std::list<int> pair;

			std::list<int>::iterator iter = list.begin();
			std::list<int>::iterator iter2 = list.begin();
			std::advance(iter, i);
			std::advance(iter2, behind);

			if (*iter)
				pair.push_back(*iter);
			else
				pair.push_back(0);
			if (*iter2 && behind != list.size())
			{
				pair.push_back(*iter2);
				behind++;
			}
			else
				pair.push_back(0);
			result.push_back(pair);
		}
		unsigned int i = list.size() - 1;
		std::list<int>::iterator iter3 = list.begin();
		std::advance(iter3, i);
		if (*iter3)
		{
			std::list<int> pair;
			pair.push_back(0);
			pair.push_back(*iter3);
			result.push_back(pair);
		}
	}

	std::list<int> half;
	for (unsigned int j = 0; j < list.size() / 2; j++)
	{
		std::list<int>::iterator iter = list.begin();
		std::advance(iter, j);
		half.push_back(*iter);
	}
	
	list_sort(half);

	// std::cout << "==================================\n";
	// res랑 result를 넘긴 다음
	//res에는 result에 첫 번재 요소들
	//pend 두 번째 요소들
	resFindPair_list(result);

	//res와 pend를 이용해서 야콥스탈의 수를 사용해서 정렬한 후엔 res에 정렬된 값이 들어있다.
	sort_j_list();
	
	
	//반으로 나눠서 짝을 지은 후 정렬(짝지은 것 끼리만)
	//vector_sort(짝지은 벡터의 앞에 것);
	//res 벡터에 맞는 짝을 찾아서 pend 배열 생성
	//야콥스탈 수를 이용해서 정렬 후 res에 저장
}


void PmergeMe::resFindPair_list(std::list<std::list<int> > &result)
{
	if (res_list.empty())
	{
		std::list<std::list<int> >::iterator iter = result.begin();
		for (; iter != result.end(); iter++)
		{
			std::list<int>::iterator iter2 = iter->begin();
			int count = 0;
			for (; iter2 != iter->end(); iter2++)
			{
				if (count == 0)
				{
					this->mainchin_list.push_back(*iter2);
				}
				else if (count == 1)
					this->pending_list.push_back(*iter2);
				count++;
			}
		}
		
	}
	else
	{

	
		std::list<int>::iterator res_iter = res_list.begin();
		int count = 0;
		for ( ; res_iter != res_list.end(); res_iter++)
		{
			for (std::list<std::list<int> >::iterator result_iter = result.begin(); result_iter != result.end(); result_iter++)
			{
				std::list<int>::iterator iter = result_iter->begin();
		
				if (*res_iter == *iter)
				{
					std::list<std::list<int> >::iterator iter2 = result.begin();
					std::advance(iter2, count);

					std::list<int>::iterator iter3 = iter2->begin();
					std::swap(*iter3, *iter);
					iter3++;
					iter++;
					std::swap(*iter3, *iter);
				}
			}
			count++;
		}

		//값 넣어주기

		std::list<std::list<int> >::iterator iter = result.begin();
		for (; iter != result.end(); iter++)
		{
			std::list<int>::iterator iter2 = iter->begin();
			int count = 0;
			for (; iter2 != iter->end(); iter2++)
			{
				if (count == 0)
				{
					this->mainchin_list.push_back(*iter2);
				}
				else if (count == 1)
					this->pending_list.push_back(*iter2);
				count++;
			}
		}
	}
}


void PmergeMe::sort_j_list(void)
{
	//res와 pend를 이용해서 야콥스탈의 수를 사용해서 정렬한 후엔 res에 정렬된 값이 들어있다.
	
	res_list.clear();

	int mainchin_size = 0;

	/* mainchin 안에 0이 없을 때 그냥 size 반환*/
	/* 아니면 다시 계산*/
	std::list<int>::iterator iter;
    iter = std::find(mainchin_list.begin(), mainchin_list.end(), 0);
    if (iter == mainchin_list.end())
	{
		mainchin_size = mainchin_list.size();
	}
	else
	{
		std::list<int>::iterator size_iter = mainchin_list.begin();
		while(1)
		{
			if (*size_iter == 0)
			{
				mainchin_size++;
				break;
			}
			size_iter++;
			mainchin_size++;
		}

	}

	int count = 0;
	int jascbsthal;
	int prev = 0;
	int pending_index = 0;
	int mainchin_index = 0;

	while(count < mainchin_size)
	{
		if (static_cast<int>(this->jascbsthal.size()) == count)
			break ;
		jascbsthal = this->jascbsthal[count];

		/* pending 넣기 */
		if (jascbsthal != 1)
		{
			int input = 0; 
			int check_size = pending_index;
			check_size = static_cast<int>(pending_list.size()) - pending_index;
			while (input < jascbsthal - prev && input != static_cast<int>(pending_list.size()) && check_size )
			{
				std::list<int>::iterator pending_iter = pending_list.begin();
				std::advance(pending_iter, pending_index);
				if (*pending_iter == 0)
					break ;
				binaryInsertionSort_list(*pending_iter);
				pending_index++;
				input++;
				check_size--;
			}
		}
		else
		{
			std::list<int>::iterator pending_iter1 = pending_list.begin();
			std::advance(pending_iter1, pending_index);
			this->res_list.push_back(*pending_iter1);
			pending_index++;
		}

		// /* mainchin 넣기 */
		int mainchin_input = 0; 
		int check_size2 = mainchin_index;
		check_size2 = static_cast<int>(mainchin_list.size()) - mainchin_index;
		while (mainchin_input < jascbsthal - prev && mainchin_input != static_cast<int>(mainchin_list.size()) && check_size2)
		{
			std::list<int>::iterator mainchin_iter = mainchin_list.begin();
			std::advance(mainchin_iter, mainchin_index);
 			if (*mainchin_iter == 0)
					break ;
			binaryInsertionSort_list(*mainchin_iter);
			mainchin_index++;
			mainchin_input++;
			check_size2--;
		}
		prev = jascbsthal;
		count++;
	}
	this->mainchin_list.clear();
	this->pending_list.clear();
	
}


void PmergeMe::binaryInsert_list(std::list<int>& arr, int element) 
{
    std::list<int>::iterator left = arr.begin();
    std::list<int>::iterator right = arr.end();
    
    while (left != right) {
        std::list<int>::iterator mid = left;
        std::advance(mid, std::distance(left, right) / 2);

        if (*mid == element)
		{
            arr.insert(mid, element);
            return;
        } else if (*mid < element) {
            ++left;
        } else {
            --right;
        }
    }

    arr.insert(left, element);
}


void PmergeMe::binaryInsertionSort_list(int elemnt) 
{
	binaryInsert_list(this->res_list, elemnt);
}


void PmergeMe::calc_jascbsthal(std::vector<int> vector)
{
	int vector_size = vector.size();
	double prev = 1;
	double result;

	int count = 0;
	while (vector_size)
	{
		if (vector_size == 1)
		{
			count++;
			break;
		}
		count++;
		vector_size = vector_size / 2;
	}
	for (int i = 1; i <= count; i++)
	{
		result = 1;
		for (int j = 0; j < i; j++)
		{
			result *= 2;
		}
		jascbsthal.push_back(result - prev);
		prev = result - prev;
    }
}


void PmergeMe::binaryInsert(std::vector<int>& arr, int element) 
{
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == element) {
            arr.insert(arr.begin() + mid, element);
            return;
        } else if (arr[mid] < element) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    arr.insert(arr.begin() + left, element);
}

void PmergeMe::binaryInsertionSort(int elemnt) 
{
	binaryInsert(this->res, elemnt);
}

void PmergeMe::sort_j(void)
{
	//res와 pend를 이용해서 야콥스탈의 수를 사용해서 정렬한 후엔 res에 정렬된 값이 들어있다.
	res.clear();

	int mainchin_size = 0;

	/* mainchin 안에 0이 없을 때 그냥 size 반환*/
	/* 아니면 다시 계산*/
	std::vector<int>::iterator iter;
    iter = std::find(mainchin.begin(), mainchin.end(), 0);
    if (iter == mainchin.end())
	{
		std::cout << "mainchin_size : " << mainchin_size << std::endl;
		mainchin_size  = mainchin.size();
	}
	else
	{
		while(1)
		{
			if (this->mainchin[mainchin_size] == 0)
			{
				mainchin_size++;
				break ;
			}
			mainchin_size++;
		}

	}


	int count = 0;
	int jascbsthal;
	int prev = 0;
	int pending_index = 0;
	int mainchin_index = 0;

	while(count < mainchin_size)
	{
		if (static_cast<int>(this->jascbsthal.size()) == count)
			break ;
		jascbsthal = this->jascbsthal[count];
	
		/* pending 넣기 */
		if (jascbsthal != 1)
		{
			int input = 0; 
			int check_size = pending_index;
			check_size = static_cast<int>(pending.size()) - pending_index;
			while (input < jascbsthal - prev && input != static_cast<int>(pending.size()) && check_size )
			{
				if (pending[pending_index] == 0)
					break ;
				binaryInsertionSort(pending[pending_index]);
				pending_index++;
				input++;
				check_size--;
			}
		}
		else
		{
			this->res.push_back(pending[pending_index]);
			pending_index++;
		}

		/* mainchin 넣기 */
		int mainchin_input = 0; 
		int check_size2 = mainchin_index;
		check_size2 = static_cast<int>(mainchin.size()) - mainchin_index;
		while (mainchin_input < jascbsthal - prev && mainchin_input != static_cast<int>(mainchin.size()) && check_size2)
		{
 			if (mainchin[mainchin_index] == 0)
					break ;
			binaryInsertionSort(mainchin[mainchin_index]);
			mainchin_index++;
			mainchin_input++;
			check_size2--;
		}
		prev = jascbsthal;
		count++;
		
	}
	this->mainchin.clear();
	this->pending.clear();
}

void PmergeMe::resFindPair(std::vector<std::vector<int> > &result)
{
	if (res.empty())
	{
		for (unsigned int i = 0; i < result.size(); i++)
		{
			for (unsigned int j = 0; j < result[i].size(); j++)
			{
				if (j == 0)
					this->mainchin.push_back(result[i][j]);
				else if (j == 1)
					this->pending.push_back(result[i][j]);

			}
		}
	}
	else
	{
		for (size_t i = 0; i < this->res.size(); i++)
		{
			for (size_t j = i + 1; j < result.size(); j++)
			{
				if (this->res[i] == result[j][0])
					std::swap(result[i], result[j]);
			}
		}

		//값 넣어주기
		for (unsigned int i = 0; i < result.size(); i++)
		{
			for (unsigned int j = 0; j < result[i].size(); j++)
			{
				if (j == 0)
					this->mainchin.push_back(result[i][j]);
				else if (j == 1)
					this->pending.push_back(result[i][j]);

			}
		}
	}
}

void PmergeMe::vector_sort(std::vector<int> &vector)
{
	std::vector<std::vector<int> > result;


    if (vector.size() == 1)
		return;

	//1. 인자값을 반으로 나눈 다음에 중간을 통해 큰 거 앞으로 작은 거 뒤로
	unsigned int behind;
	behind = vector.size() / 2;		
	for (unsigned int i = 0; i < vector.size() / 2; i++)
	{
		if (vector[i] < vector[behind])
		{
			std::swap(vector[i], vector[behind]);
		}
		behind++;
	}

	//2. 정렬된 친구들 벡터 안에 벡터로 묶어주기

	if (vector.size() % 2 == 0)
	{
		unsigned int behind;
		behind = vector.size() / 2;
		for (  unsigned int i = 0; i < vector.size() / 2; i++)
		{
			std::vector<int> pair;
			if (vector[i])
				pair.push_back(vector[i]);
			else
				pair.push_back(0);
			if (vector[behind])
			{
				pair.push_back(vector[behind]);
				behind++;
			}
			else
				pair.push_back(0);
			result.push_back(pair);
		}
	}
	else
	{
		unsigned int behind;
		behind = vector.size() / 2;
		for (unsigned int i = 0; i < vector.size() / 2; i++)
		{
			std::vector<int> pair;
			if (vector[i])
				pair.push_back(vector[i]);
			else
				pair.push_back(0);
			if (vector[behind] && behind != vector.size())
			{
				pair.push_back(vector[behind]);
				behind++;
			}
			else
				pair.push_back(0);
			result.push_back(pair);
		}
		unsigned int i = vector.size() - 1;
		if (vector[i])
		{
			std::vector<int> pair;
			pair.push_back(0);
			pair.push_back(vector[i]);
			result.push_back(pair);
		}
	}

	std::vector<int> half;
	for (unsigned int j = 0; j < vector.size() / 2; j++)
	{
		half.push_back(vector[j]);
	}
	
	vector_sort(half);
	// res랑 result를 넘긴 다음
	//res에는 result에 첫 번재 요소들
	//pend 두 번째 요소들
	resFindPair(result);

	//res와 pend를 이용해서 야콥스탈의 수를 사용해서 정렬한 후엔 res에 정렬된 값이 들어있다.
	sort_j();
	//반으로 나눠서 짝을 지은 후 정렬(짝지은 것 끼리만)
	//vector_sort(짝지은 벡터의 앞에 것);
	//res 벡터에 맞는 짝을 찾아서 pend 배열 생성
	//야콥스탈 수를 이용해서 정렬 후 res에 저장

}


void PmergeMe::handleError(std::string message) {
    std::cerr << message << "\n";
    std::exit(1);
}

