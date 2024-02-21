// #include <iostream>
// #include <list>

// int main() {
//     // 정수형 리스트 생성
//     std::list<int> myList;

//     myList.push_back(1);
//     myList.push_back(2);
//     myList.push_back(3);
//     myList.push_back(4);
//     myList.push_back(5);

//     std::cout << myList[1] << std::endl;

//     // 첫 번째 원소에 접근
//     std::list<int>::iterator firstElement = myList.begin();
//     std::cout << "First element: " << *firstElement << std::endl;

//     // 마지막 원소에 접근
//     std::list<int>::iterator lastElement = --myList.end(); // end()는 마지막 원소의 다음을 가리키므로, 이전 원소를 가리키도록 -- 연산자 사용
//     std::cout << "Last element: " << *lastElement << std::endl;



//     return 0;
// }

#include <iostream>
#include <list>

int main() {
    // 정수형 벡터 생성
    std::list<int> numbers;

    numbers.push_back(1);
    numbers.push_back(2);
    numbers.push_back(3);
    numbers.push_back(4);
    numbers.push_back(5);

    //3. find 함수
    std::list<int>::iterator list_iter;
    list_iter = std::find(numbers.begin(), numbers.end(), 2);
    std::cout << "list_iter : " << *list_iter << std::endl;


    return 0;
}