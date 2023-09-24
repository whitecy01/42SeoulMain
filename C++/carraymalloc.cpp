#include <iostream>

int main()
{
	int num = 3;

	double *ptr = new double[num];
	for (int i = 0; i < 3; i++)
	{
		ptr[i] = i + 1.1;
		std::cout << "ptr[" << i << "] : " << ptr[i] << "\n"; 
	}

	delete []ptr;

}