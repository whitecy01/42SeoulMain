#include <iostream>

using namespace std;

class Parent
{
private:
	int num1;
public:
	int num2;
protected:
	int num3;
};

class Base : private Parent 
{
public:
	Base()
	{
		num2 = 1;
		num3 = 2;
		cout << this->num2 << endl; // error!
		cout << this->num3 << endl; // error!
	};

	int getNum2()
	{
		return num2;
	};

	int getNum3()
	{
		return num3;
	};
};

int main()
{
	Base base;

	cout << base.getNum2() << endl; // error!
	cout << base.getNum3() << endl; // error!
	return 0;
}