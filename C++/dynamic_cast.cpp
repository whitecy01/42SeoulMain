#include <iostream>
#include <string>
#include <vector>

class Animal {
public:
    virtual void sound() = 0;
    void info(){
        std::cout << "동물은 숨을 쉽니다.\n";
    }
    virtual ~Animal() {}
};

class Dog : public Animal{
private:
    std::string name;
public:
    Dog(std::string s) : name(s) {};
    void sound() { std::cout << "멍멍\n"; }
    void name_print() { std::cout << name << std::endl; }
    void only_dog() { std::cout << "이건 개 클래스\n"; }
    ~Dog() {}
};

class Cat : public Animal {
private:
    std::string name;
public:
    Cat(std::string s) : name(s) {};
    void sound() { std::cout << "냐옹\n"; }
    void name_print() { std::cout << name << std::endl; }
    void data() { std::cout << this << std::endl; }
    void only_cat() { std::cout << "이건 고양이 클래스\n"; }
    ~Cat() {}
};

int main() {

    std::vector<Animal*> v;
    v.__emplace_back(new Cat("나비"));
    v.__emplace_back(new Dog("멍멍이"));



    delete v[0];
    v[0] = nullptr;
    delete v[1];
    v[1] = nullptr;

    return 0;
}
