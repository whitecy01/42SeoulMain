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


// left 0 right 5
void PmergeMe::vector_sort(std::vector<int> &vector)
{
	std::vector<std::vector<int> > result;

	(void) left;
	(void) right;

    // 주어진 요소들을 두 개씩 묶어서 결과 벡터에 추가
    if (vector.size() == 1)
		return;
	반으로 나눠서 짝을 지은 후 정렬(짝지은 것 끼리만)
	vector_sort(짝지은 벡터의 앞에 것);
	res 벡터에 맞는 짝을 찾아서 pend 배열 생성
	야콥스탈 수를 이용해서 정렬 후 res에 저장
// 	for (  unsigned int i = 0; i < vector.size(); i += 2) {
//         std::vector<int> pair;
//         pair.push_back(vector[i]);
//         pair.push_back(vector[i + 1]);
//         result.push_back(pair);
//     }

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

double PmergeMe::calc_jascbsthal(size_t number, double Jacobsthal_number)
{
	double result = 1;
	for (size_t i = 0; i < number; i++) {
        result *= 2;
    }
	return result - Jacobsthal_number;

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

