#include <stdio.h>

int main()
{
	float result = 0.0;
	int i = 0;

	for (i = 0 ; i< 100; i++)
	{
		result += 0.1;
	}
	printf("%f \n", result);
}