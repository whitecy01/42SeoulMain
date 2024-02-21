// #include <vector>
// #include <iostream>

// using namespace std;
// int main()
// {
// 	{
// 		std::vector<int> vec;
// 		for (int i = 0; i < 10; ++i)
// 			vec.push_back(i);
// 		// for (auto& itr : vec)
// 		// 	cout << itr << "  ";
//         for (int i = 0; i < 10; ++i)
// 			cout << vec[i] << " ";
// 		cout << "\n";
// 	}
// }

// #include <iostream>
// #include <vector>

// int main() {
//     // 정수형 벡터 생성
//     std::vector<int> numbers;

//     // 벡터에 값 추가
//     numbers.push_back(10);
//     numbers.push_back(20);
//     numbers.push_back(30);

//     // 벡터의 크기 출력
//     std::cout << "Vector size: " << numbers.size() << std::endl;

//     // 벡터의 각 원소 출력
//     std::cout << "Vector elements:";
//     for (size_t i = 0; i < numbers.size(); ++i) {
//         std::cout << " " << numbers[i];
//     }
//     std::cout << std::endl;

//     // 벡터의 각 원소에 5를 더하여 출력
//     std::cout << "Vector elements after adding 5:";
//     for (size_t i = 0; i < numbers.size(); ++i) {
//         std::cout << " " << numbers[i] + 5;
//     }
//     std::cout << std::endl;

//     return 0;
// }

#include <iostream>
#include <vector>

int main() {
    // 정수형 벡터 생성
    std::vector<int> numbers;

    numbers.push_back(1);
    numbers.push_back(2);
    numbers.push_back(3);
    numbers.push_back(4);
    numbers.push_back(5);

    // begin()과 end()를 사용하여 벡터의 모든 원소 출력
    // 1. C++11에 있는 auto 
    std::cout << "Vector elements:";
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << " " << *it;
    }
    std::cout << std::endl;

    //2. 명시적인 반복자 타입 iterator
    std::vector<int>::iterator iter;
    std::cout << "Vector elements:";
    for (iter = numbers.begin(); iter != numbers.end(); ++iter) {
        std::cout << " " << *iter;
    }
    std::cout << std::endl;

    //3. find 함수
    std::vector<int>::iterator vector_iter;
    vector_iter = std::find(numbers.begin(), numbers.end(), 2);
    std::cout << "vector_iter : " << *vector_iter << std::endl;


    return 0;
}
