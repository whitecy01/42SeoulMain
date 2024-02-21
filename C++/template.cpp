// #include <iostream>

// // 함수 템플릿 정의
// template <typename T>
// void swapValues(T& a, T& b) {
//     T temp = a;
//     a = b;
//     b = temp;
// }

// int main() {
//     int x = 5, y = 10;
//     std::cout << "Before swapping: x = " << x << ", y = " << y << std::endl;

//     // 함수 템플릿 호출
//     swapValues(x, y);

//     std::cout << "After swapping: x = " << x << ", y = " << y << std::endl;
    
//     double a = 2, b = 4;
//     std::cout << "Before swapping: a = " << a << ", b = " << b << std::endl;

//     // 함수 템플릿 호출
//     swapValues(a, b);

//     std::cout << "After swapping: a = " << a << ", b = " << b << std::endl;

//     std::string str = "hi", str2 = "hello";
//     std::cout << "Before swapping: str = " << str << ", str2 = " << str2 << std::endl;

//     // 함수 템플릿 호출
//     swapValues(str, str2);

//     std::cout << "After swapping: str = " << str << ", str2 = " << str2 << std::endl;

//     return 0;
// }

#include <iostream>
#include <vector>
#include <stdexcept>

// 클래스 템플릿 정의
template <typename T>
class Stack {
private:
    std::vector<T> elements;
public:
    void push(const T& element) {
        elements.push_back(element);
    }
    T pop() {
        if (elements.empty()) {
            throw std::out_of_range("Stack<>::pop(): empty stack");
        }
        T elem = elements.back();
        elements.pop_back();
        return elem;
    }
};

int main() {
    // 정수형 스택 객체 생성
    Stack<int> intStack;
    intStack.push(5);
    intStack.push(10);
    std::cout << "Popped element: " << intStack.pop() << std::endl;

    // 실수형 스택 객체 생성
    Stack<double> doubleStack;
    doubleStack.push(3.14);
    doubleStack.push(2.71);
    std::cout << "Popped element: " << doubleStack.pop() << std::endl;

    return 0;
}
