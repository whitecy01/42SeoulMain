#include <iostream>

class Animal {
public:
    virtual void sound() {
        std::cout << "동물 소리\n";
    }
};

class Dog : public Animal {
public:
    void sound()  {
        std::cout << "멍멍\n";
    }
};

int main() {
    Animal* animalPtr = new Dog;
    Dog* dogPtr = dynamic_cast<Dog*>(animalPtr);

    if (dogPtr) {
        dogPtr->sound(); // 동물의 실제 타입에 따라 올바른 소리 출력
    }

    delete animalPtr;
    return 0;
}
