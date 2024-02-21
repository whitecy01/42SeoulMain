// #include <iostream>

// int main() {
//     int intValue = 42;

//     // int 포인터를 double 포인터로 reinterpret_cast 형변환
//     int *intPointer = &intValue;
//     double *doublePointer = reinterpret_cast<double*>(intPointer);

//     // double 포인터를 사용하여 값 출력
//     std::cout << "int 값: " << intValue << std::endl;
//     std::cout << "double 값: " << *doublePointer << std::endl;

//     return 0;
// }

// #include <iostream>

// int main() {


//     // int를 double로 안전하게 형변환
//     int intValue = 42;
//     double doubleValue = static_cast<double>(intValue);

//     std::cout << "int 값: " << intValue << std::endl;
//     std::cout << "double 값: " << doubleValue << std::endl;

//     return 0;
// }

#include <iostream>

class Base {
public:
    virtual ~Base() {}
};

class Derived : public Base {};

int main() {
    Base* basePtr = new Derived;

    // Derived 타입으로 안전하게 형변환
    if (Derived* derivedPtr = dynamic_cast<Derived*>(basePtr)) {
        std::cout << "다형성을 통한 안전한 형변환 성공!" << std::endl;
    } else {
        std::cout << "다형성을 통한 형변환 실패" << std::endl;
    }

    delete basePtr;
    return 0;
}

