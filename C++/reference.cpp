#include <iostream>

void func(int& a){ a *= 2; }

//void func(int* ptr) { *ptr *= 2; }

// int num = 3;
// func(&num); // call by address

int main()
{
	int num = 3;
	func(num);
	std::cout << num << "\n";
}
