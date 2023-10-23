#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

void measureSortingTime() {
    std::vector<int> data(10000000);
    for (int i = 0; i < 10000000; i++) {
        data[i] = rand();
    }

    std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();

    std::sort(data.begin(), data.end());

    std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();

    std::chrono::microseconds elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "정렬에 걸린 시간: " << elapsed_time.count() << " 마이크로초" << std::endl;
}

int main() {
    measureSortingTime();

    return 0;
}
