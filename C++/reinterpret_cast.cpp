#include <iostream>

int main() {
    // int 타입의 변수
    int intValue = 42;

    // int 포인터를 void 포인터로 형변환
    void* voidPointer = reinterpret_cast<void*>(&intValue);

    // void 포인터를 다시 int 포인터로 형변환
    int* intPointer = reinterpret_cast<int*>(voidPointer);

    // 결과 출력
    std::cout << "원래 값: " << *intPointer << std::endl;

    return 0;
}
