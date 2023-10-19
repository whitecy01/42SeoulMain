
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

    std::vector<int> left_arr(n1);
    std::vector<int> right_arr(n2);

    for (int i = 0; i < n1; i++) {
        left_arr[i] = arr[left + i];
    }

    for (int i = 0; i < n2; i++) {
        right_arr[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (left_arr[i] <= right_arr[j]) {
            arr[k] = left_arr[i];
            i++;
        } else {
            arr[k] = right_arr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = left_arr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = right_arr[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

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

