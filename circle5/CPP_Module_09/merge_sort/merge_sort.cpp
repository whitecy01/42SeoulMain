
// #include <iostream>
// #include <limits.h>

// # define MAX_SIZE 8


// int main()
// {
// 	int i;
// 	int n = MAX_SIZE;
// 	int list[n] = {21, 10, 12, 20, 25, 13, 15, 22};

// 	// 합병 정렬 수행(left: 배열의 시작 = 0, right: 배열의 끝 = 7)
// 	merge_sort(list, 0, n-1);

// 	// 정렬 결과 출력
// 	for(i=0; i<n; i++){
// 	printf("%d\n", list[i]);
// 	}

// }
#include <iostream>
#include <vector>

void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::cout << "n1 : " << n1 << " n2 : " << n2 << std::endl;
            std::cout << "left : " << left << " mid : "<<  mid << " right : "<<  right<< std::endl;
            
    std::vector<int> left_arr(n1);
    std::vector<int> right_arr(n2);


    for (int i = 0; i < n1; i++) {
        left_arr[i] = arr[left + i];
    }

    for (int i = 0; i < n2; i++) {
        right_arr[i] = arr[mid + 1 + i];
    }

        std::cout << "left_arr\n";
    std::cout << "left_arr.size() : " << left_arr.size() << std::endl;
    for (int i = 0; i < left_arr.size(); i++) {
        std::cout << left_arr[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "right_arr\n";
    std::cout << "right_arr.size() : " << right_arr.size() << std::endl;
    for (int i = 0; i < right_arr.size(); i++) {
        std::cout << right_arr[i] << " ";
    }
    
    std::cout << std::endl;


    int i = 0, j = 0, k = left;

    
    std::cout << "arr\n";
    for (int q = 0; q < arr.size(); q++) 
    {
        std::cout << arr[q] << " ";
    }
    std::cout << "\n";

    while (i < n1 && j < n2) 
    {
        if (left_arr[i] <= right_arr[j]) {
            arr[k] = left_arr[i];
            i++;
        } else {
            std::cout << "k : " << k << std::endl;
            arr[k] = right_arr[j];
            j++;
        }
        k++;
    }

    std::cout << "arr\n";
    for (int q = 0; q < arr.size(); q++) 
    {
        std::cout << arr[q] << " ";
    }
    std::cout << "\n";


    while (i < n1) 
    {
        arr[k] = left_arr[i];
        i++;
        k++;
    }

    std::cout << "arr\n";
    for (int e = 0; e < arr.size(); e++) 
    {
        std::cout << arr[e] << " ";
    }
    std::cout << "\n";

    while (j < n2) {
        arr[k] = right_arr[j];
        j++;
        k++;
    }

        std::cout << "arr\n";
    for (int x = 0; x < arr.size(); x++) 
    {
        std::cout << arr[x] << " ";
    }
    std::cout << "\n";
}

void mergeSort(std::vector<int>& arr, int left, int right)
{
    if (left < right) 
    {
        std::cout << "left : " << left << " right : "<<  right<< std::endl;
        int mid = left + (right - left) / 2;
        std::cout << "mid : " << mid << std::endl;
        mergeSort(arr, left, mid);
        std::cout << "come_to_second_mergeSort" << std::endl;
        std::cout << "mid + 1 : " << mid + 1 << " right : "<<  right<< std::endl;
        mergeSort(arr, mid + 1, right);
        
        std::cout << "==============merge============\n";
        std::cout << "left : " << left << " mid : "<<  mid << " right : "<<  right<< std::endl;
        merge(arr, left, mid, right);
    }
}

int main() {
    std::vector<int> arr;

	arr.push_back(12);
	arr.push_back(11);
	arr.push_back(13);
	arr.push_back(5);
	arr.push_back(6);
	arr.push_back(7);
    arr.push_back(8);
    
    arr.push_back(10);
    int arr_size = arr.size();

    std::cout << "원래 배열: ";
    for (int i = 0; i < arr_size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    mergeSort(arr, 0, arr_size - 1);

    std::cout << "정렬된 배열: ";
    for (int i = 0; i < arr_size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}

