#include <iostream>
#include <algorithm> // std::find 함수를 사용하기 위해 포함해야 함
#include <vector>

int main() {
    // 정수형 벡터 생성
    std::vector<int> numbers;

    numbers.push_back(1);
    numbers.push_back(2);
    numbers.push_back(3);
    numbers.push_back(4);
    numbers.push_back(5);

    // 찾을 값 정의
    int valueToFind = 3;

    // std::find 함수를 사용하여 벡터에서 지정된 값 찾기
    std::vector<int>::iterator it = std::find(numbers.begin(), numbers.end(), valueToFind);

    // 결과 확인
    if (it != numbers.end()) {
        std::cout << "Value " << valueToFind << " found at index " << std::distance(numbers.begin(), it) << std::endl;
    } else {
        std::cout << "Value " << valueToFind << " not found in the vector" << std::endl;
    }

    return 0;
}
