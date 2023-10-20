#include <iostream>
#include <vector>

int main() {
    // 주어진 요소들을 벡터에 저장
    std::vector<int> elements;
    elements.push_back(11);
    elements.push_back(7);
    elements.push_back(5);
    elements.push_back(3);
    elements.push_back(20);
    elements.push_back(22);

    // 결과를 저장할 벡터 생성
    std::vector<std::vector<int> > result;

    // 주어진 요소들을 두 개씩 묶어서 결과 벡터에 추가
    for (int i = 0; i < elements.size(); i += 2) {
        std::vector<int> pair;
        pair.push_back(elements[i]);
        pair.push_back(elements[i + 1]);
        result.push_back(pair);
    }

    // 결과 출력
    for (size_t i = 0; i < result.size(); ++i) {
        for (size_t j = 0; j < result[i].size(); ++j) {
            std::cout << result[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
