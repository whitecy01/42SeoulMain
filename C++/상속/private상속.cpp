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
			//num1 = 3;
			num2 = 1;
			num3 = 2;
		}

};
int main()
{
	Base base;

	cout << base.num1 << endl; // error!
	cout << base.num2 << endl; // error!
	cout << base.num3 << endl; // error!
	return 0;
}