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

class Base : public Parent {


public:
	Base(){
		num2 = 2;
		num3 = 1;
		cout << num3 << endl; // ok!
	}
 };
int main()
{
	Base base;

	//cout << base.num1 << endl; // error!
	cout << base.num2 << endl; // ok!
	//cout << base.num3 << endl; // error!
	return 0;
}