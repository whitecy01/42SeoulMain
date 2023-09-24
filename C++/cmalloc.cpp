#include <iostream>

int main()
{
	//1바이트 만큼 heap 할당
	char *ptr = new char;
	*ptr = 'a';
	std::cout << "메모리 주소 : " << (void *)ptr << "\t 값 : " << *ptr << "\n";
	std::cout << "heap의 크기 : " << sizeof(*ptr) << std::endl;

	//4바이트 만큼 heap에 할당
	int *ptr1 = new int;
	*ptr1 = 3;
	std::cout << "메모리 주소 : " << ptr1 << "\t 값 : " << *ptr1 << "\n";
	std::cout << "heap의 크기 : " << sizeof(*ptr1) << std::endl;

	//4바이트 만큼 heap에 할당
	float *pfloat = new float;
	*pfloat = 3.14;
	std::cout << "메모리 주소 : " << pfloat << "\t 값 : " << *pfloat << "\n";
	std::cout << "heap의 크기 : " << sizeof(*pfloat) << std::endl;

	//8바이트 만큼 heap에 할당
	double *pdouble = {new double};
	*pdouble = 3.141592;
	std::cout << "메모리 주소 : " << (void *)pdouble << "\t 값 : " << *pdouble << "\n";
	std::cout << "heap의 크기 : " << sizeof(*pdouble) << std::endl;
	delete pdouble;
	delete ptr;
	delete ptr1;
	delete pfloat;


}