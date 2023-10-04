#include "Polymorphism.hpp"

int main()
{
    const Animal* j = new Dog();
    const Animal* i = new Cat();
    delete j;
    delete i;
    Animal  *a[4];
    for(int i=0; i<4; i++)
    {
        if (i < 2)
            a[i] = new Cat();
        else
            a[i] = new Dog();
    }
    for(int i=0; i<4; i++)
        a[i]->makeSound();
    for(int i=0; i<4; i++)
        delete a[i];

	Dog *dog = new Dog();
	Dog *dog2 = new Dog();
	Cat *cat = new Cat();
	Cat *cat2 = new Cat();
	std::cout << dog->getDogIdea(2) << std::endl;
	std::cout << dog2->getDogIdea(2) << std::endl;
	std::cout << cat->getCatIdea(2) << std::endl;
	std::cout << cat2->getCatIdea(2) << std::endl;

	dog->setBrain(2, "hello");
	dog2->setBrain(2, "dog2");
	cat->setBrain(2, "aaa");
	cat2->setBrain(2, "acb");
	*cat2 = *cat;
	*dog2 = *dog;

	std::cout << dog->getDogIdea(2) << std::endl;
	std::cout << dog2->getDogIdea(2) << std::endl;
	std::cout << cat->getCatIdea(2) << std::endl;
	std::cout << cat2->getCatIdea(2) << std::endl;

	delete dog;
	delete dog2;
	delete cat;
	delete cat2;
    return 0;
}
