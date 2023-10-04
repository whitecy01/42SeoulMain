
//rtti -> 
class Animal
{
	int hp;
	int	hunger;

	virtual ~Animal();
	virtual getHP()
		return hp;
}
8byte

class Dog : Animal
{
	vtable *vtable;
	int b;
	//int	*a = new int[6];
	//Aniaml *ptr = new Animal();
	getHP(){
		return hp * 2;
	}
}
8 + 4byte = 12

struct Dog
{
	Animal base;
	int		a;
}

Animal *animal = new Animal();

Animal * animal = malloc(sizeof(Animal));
Animal(animal);

Animal *dog = new Dog();
Dog(dog);
delete dog;

dog->getHP();
dog->vtable->getHP();

Dog basic
{
	Dog tmp = basic;
// Dog d;
// Animal *ptr = &d;
}
