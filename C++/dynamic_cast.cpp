// #include <iostream>
// #include <string>
// #include <stack>
// #include <vector>

// class Animal {
// public:
//     virtual void sound() = 0;
//     void info(){
//         std::cout << "동물은 숨을 쉽니다.\n";
//     }
//     virtual ~Animal() {}
// };

// class Dog : public Animal{
// private:
//     std::string name;
// public:
//     Dog(std::string s) : name(s) {};
//     void sound() { std::cout << "멍멍\n"; }
//     void name_print() { std::cout << name << std::endl; }
//     void only_dog() { std::cout << "이건 개 클래스\n"; }
//     ~Dog() {}
// };

// class Cat : public Animal {
// private:
//     std::string name;
// public:
//     Cat(std::string s) : name(s) {};
//     void sound() { std::cout << "냐옹\n"; }
//     void name_print() { std::cout << name << std::endl; }
//     void data() { std::cout << this << std::endl; }
//     void only_cat() { std::cout << "이건 고양이 클래스\n"; }
//     ~Cat() {}
// };

// int main() {

// std::deque<int> s;
// std::stack<int> a;
//     std::vector<Animal*> v;
//     v.__emplace_back(new Cat("나비"));
//     v.__emplace_back(new Dog("멍멍이"));



//     delete v[0];
//     v[0] = nullptr;
//     delete v[1];
//     v[1] = nullptr;

//     return 0;
// }


#include <iostream>

class Base {
public:
    virtual void print() const {
        std::cout << "Base 클래스" << std::endl;
    }
    virtual ~Base() {}
};

class Derived : public Base {
public:
    void print() const  {
        std::cout << "Derived 클래스" << std::endl;
    }
};

int main() {
    Base baseObj;
    Derived derivedObj;

    Base* ptrBase = &derivedObj;

    // dynamic_cast를 사용하여 Derived*로 안전하게 형변환
    if (Derived* ptrDerived = dynamic_cast<Derived*>(ptrBase)) {
        std::cout << "다형성을 통한 dynamic_cast 성공!" << std::endl;
        ptrDerived->print(); // Derived 클래스의 print 함수 호출
    } else {
        std::cout << "다형성을 통한 dynamic_cast 실패" << std::endl;
    }


    return 0;
}
