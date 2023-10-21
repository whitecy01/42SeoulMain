#include "PmergeMe.hpp"
int num = 1;
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


	calc_jascbsthal(this->vector);
	vector_sort(vector);
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
			break;
		count++;
		vector_size = vector_size / 2;
	//std::cout << vector_size << std::endl;
	}
	//std::cout << "count : " << count << std::endl; 
	
	

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




	// std::cout << "jascbsthal : " << std::endl;
	// for (size_t g = 0; g < jascbsthal.size(); g++)
	// {
	// 	std::cout << jascbsthal[g] << " ";
	// }
	// std::cout << std::endl;
	

}


std::vector<int> PmergeMe::merge(const std::vector<int>& left, const std::vector<int>& right) {
    std::vector<int> merged;
    size_t i = 0, j = 0;
    while (i < left.size() && j < right.size()) {
        if (left[i] > right[j]) {
            merged.push_back(left[i]);
            ++i;
        } else {
            merged.push_back(right[j]);
            ++j;
        }
    }

    while (i < left.size()) {
        merged.push_back(left[i]);
        ++i;
    }

    while (j < right.size()) {
        merged.push_back(right[j]);
        ++j;
    }

    return merged;
}


std::vector<int> PmergeMe::mergeSort(const std::vector<int>& input) {
    if (input.size() <= 1) 
        return input;

    size_t middle = input.size() / 2;
    std::vector<int> left(input.begin(), input.begin() + middle);
    std::vector<int> right(input.begin() + middle, input.end());

    left = mergeSort(left);
    right = mergeSort(right);

    return merge(left, right);
}



std::vector<int>  PmergeMe::resFindPair(std::vector<std::vector<int> > &result)
{
	if (res.empty())
	{
		std::vector<int> pending;
		for (unsigned int i = 0; i < result.size(); i++)
		{
			for (unsigned int j = 0; j < result[i].size(); j++)
			{
				if (j == 0)
					this->res.push_back(result[i][j]);
				else if (j == 1)
					pending.push_back(result[i][j]);

			}
			
		}
	}
	else
	{
		for()
		{
			
		}
	}


	return pending;
	
	
}

void PmergeMe::sort_j(std::vector<int> &pend)
{
	//res와 pend를 이용해서 야콥스탈의 수를 사용해서 정렬한 후엔 res에 정렬된 값이 들어있다.

	int count = res.size() / 2;
	if (count == 0)
		count = 1;
	int prev;


	std::vector<int> copy_res;

	for (unsigned int j = 0; j < res.size(); j++)
		copy_res.push_back(res[j]);
	
	res.clear();

	std::cout << "copy_res : " ;
	for (unsigned int a = 0; a < copy_res.size(); a++)
	{
		std::cout << copy_res[a] << " ";
	}
	std::cout << std::endl;
	std::cout << "pend : " ;
	for (unsigned int a = 0; a < pend.size(); a++)
	{
		std::cout << pend[a] << " ";
	}
	std::cout << std::endl;


	std::cout << "count : " << count << std::endl;
	for (int i = 0; i < count; i++)
	{
		
			std::cout << "jascbsthal[i] : " << jascbsthal[i] << std::endl;
		if (jascbsthal[i] == 1)
		{
			this->res.push_back(pend[0]);
			this->res.push_back(copy_res[0]);
		}
		else
		{
			for ( int copy_index = 0; copy_index < jascbsthal[i] - prev; copy_index++)
			{
				this->res.push_back(copy_res[copy_index]);
			}
			int fuck = jascbsthal[i] - 1;
			for ( int pend_index = 0; pend_index < jascbsthal[i] - prev; pend_index++)
			{
				if (jascbsthal[i] > 1)
				{
					if (pend_index == 0)
						this->res.push_back(pend[pend_index]);
					else
					{
						this->res.push_back(pend[fuck]);
						fuck--;		
					}
				}
				else
					this->res.push_back(pend[pend_index]);
			}
		}
		prev = jascbsthal[i];
	}
	std::cout << "res : " ;
	for (unsigned int a = 0; a < this->res.size(); a++)
	{
		std::cout << this->res[a] << " ";
	}
	std::cout << std::endl;
	
}

// left 0 right 5
void PmergeMe::vector_sort(std::vector<int> &vector)
{
	std::vector<std::vector<int> > result;


	std::cout << "=================in =============" << std::endl;
	std::cout << "num : " << num << std::endl;
	num++;
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
	std::cout << "vector : ";
	for (unsigned int i = 0; i < vector.size(); i++)
	{
		std::cout << vector[i] << " ";
	}
	std::cout << std::endl;

	
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


//    for (size_t i = 0; i < result.size(); ++i)
//    {
//         for (size_t j = i + 1; j < result.size(); ++j) 
// 		{
// 			if (result[i][0] == 0 || result[j][0] == 0)
// 			{
// 				continue;
// 			}
//             else if (result[i][0] > result[j][0]) 
// 			{
//                 std::swap(result[i], result[j]);
//             }

//         }
//     }

	for (unsigned int a = 0; a < result.size(); a++)
	{
		std::cout << "result : ";
		for (size_t j = 0; j < result[a].size(); j++)
		{
			std::cout  << result[a][j] << " ";
			/* code */
		}
		std::cout << std::endl;
		
 	}

	std::vector<int> half;
	for (unsigned int j = 0; j < vector.size() / 2; j++)
	{
		half.push_back(vector[j]);
	}

	// for (unsigned int a = 0; a < half.size(); a++)
	// {
	// 	std::cout << "half : " << half[a] << std::endl;
 	// }
	// std::cout << std::endl;
	

	vector_sort(half);
	std::vector<int> pend;
	// res랑 result를 넘긴 다음
	//res에는 result에 첫 번재 요소들
	//pend 두 번째 요소들
	pend = resFindPair(result);



	// std::cout << "pend : ";
	// for(unsigned int b = 0; b < pend.size(); b++)
	// {
	// 	std::cout << pend[b] << " ";
	// }
	// std::cout << std::endl;
	//res와 pend를 이용해서 야콥스탈의 수를 사용해서 정렬한 후엔 res에 정렬된 값이 들어있다.
	sort_j(pend);
	// std::cout << "res : " ;
	// for (unsigned int a = 0; a < this->res.size(); a++)
	// {
	// 	std::cout << this->res[a] << " ";
	// }
	// std::cout << std::endl;




	// std::cout << "=================out ==========\n";

	// // std::cout << jascbsthal.back() << std::endl;
	// //  jascbsthal.erase(jascbsthal.end() - 1);
	// for (unsigned int a = 0; a < result.size(); a++)
	// {
	// 	std::cout << "result : ";
	// 	for (size_t j = 0; j < result[a].size(); j++)
	// 	{
	// 		std::cout  << result[a][j] << " ";
	// 		/* code */
	// 	}
	// 	std::cout << std::endl;
		
 	// }



	// for (unsigned int a = 0; a < result.size(); a++)
	// {
	// 	std::cout << "result : ";
	// 	for (size_t j = 0; j < result[a].size(); j++)
	// 	{

	// 	}
 	// }


	//반으로 나눠서 짝을 지은 후 정렬(짝지은 것 끼리만)
	//vector_sort(짝지은 벡터의 앞에 것);
	//res 벡터에 맞는 짝을 찾아서 pend 배열 생성
	//야콥스탈 수를 이용해서 정렬 후 res에 저장



// 	/* 두 개의 결과중 큰 값이 앞으로 오게 만들어야함*/
// 	//vector_merge_sort(result, vector, 0, );
// 	for (size_t i = 0; i < result.size(); ++i) {
//         result[i] = mergeSort(result[i]);
//     }



// //    for (size_t i = 0; i < result.size() - 1; ++i) {
// //         for (size_t j = i + 1; j < result.size(); ++j) {
// //             if (result[i][0] > result[j][0]) {
// //                 std::swap(result[i], result[j]);
// //             }
// //         }
// //     }

// 	for (size_t i = 0; i < result.size(); ++i) {
//         for (size_t j = 0; j < result[i].size(); ++j) {
//             std::cout << result[i][j] << " ";
//         }
//         std::cout << std::endl;
//     }

// 	//result를 활용해 포드-존슨 넣어주기
// 	ford_John(result);




}

void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        // key보다 큰 요소들을 오른쪽으로 이동
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }

        // key를 올바른 위치에 삽입
        arr[j + 1] = key;
    }
}


void PmergeMe::ford_John(std::vector<std::vector<int> > &result)
{
	std::vector<int> mainchain;
	std::vector<int> pendingelements;

	for (size_t i = 0; i < result.size(); i++)
	{
		for (size_t j = 0; j < result[i].size(); j++)
		{
			if (j == 0)
				mainchain.push_back(result[i][j]);
			else if (j == 1)
				pendingelements.push_back(result[i][j]);
		}
	}



	// std::vector<int> output;
	// double Jacobsthal_number = 1;
	// for (size_t i = 1; i <= mainchain.size(); i++)
	// {
	// 	Jacobsthal_number = calc_jascbsthal(i , Jacobsthal_number);
	// 	std::cout << "Jacobsthal_number : " << Jacobsthal_number << "\n";
	// }
	


	// for (size_t i = 0; i < mainchain.size(); i++)
	// {
	// 	std::cout << "mainchain : " << mainchain[i];
	// 	std::cout << "\n";
	// }


	// for (size_t j = 0; j < pendingelements.size(); j++)
	// {
	// 	std::cout << "pendingelements : " << pendingelements[j];
	// 	std::cout << "\n";
	// }	
	
	

	// 	for (size_t i = 0; i < result.size(); ++i) {
    //     for (size_t j = 0; j < result[i].size(); ++j) {
    //         std::cout << result[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }
}

void PmergeMe::handleError(std::string message) {
    std::cerr << message << "\n";
    std::exit(1);
}

