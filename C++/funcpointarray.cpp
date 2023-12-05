#include <iostream>

// 덧셈 함수
int add(int a, int b) {
    return a + b;
}

// 뺄셈 함수
int subtract(int a, int b) {
    return a - b;
}

// 곱셈 함수
int multiply(int a, int b) {
    return a * b;
}

int main() {
    // 함수 포인터 배열 선언 및 초기화
    int (*functionPointers[])(int, int) = { add, subtract, multiply };

    int a = 10;
    int b = 5;

    // 함수 포인터 배열을 사용하여 각 함수 호출
    for (int i = 0; i < 3; ++i) {
        int result = functionPointers[i](a, b);
        
        switch (i) {
            case 0:
                std::cout << "Addition result: " << result << std::endl;
                break;
            case 1:
                std::cout << "Subtraction result: " << result << std::endl;
                break;
            case 2:
                std::cout << "Multiplication result: " << result << std::endl;
                break;
            default:
                break;
        }
    }

    return 0;
}
