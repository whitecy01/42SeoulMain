

#include <stdlib.h>
#include <stdio.h>
void	Quck(int *array)
{
	int tmp = array[0];
	int tmp1 = array[2];

	array[2] = tmp;
	array[0] = tmp1;
}


int main()
{

	// for(int i = 0; i < 5; i++)
	// 	printf("befort : %d\n", max[i]);
	int max[5] = {1, 2, 3, 4, 5};
	int *max1 = (int *)malloc(sizeof(int) * 5);

	for(int i = 0; i < 5; i++)
	{
		max1[i] = max[i];
	}
	Quck(max1);

	for(int i = 0; i < 5; i++)
		printf("After : %d\n", max1[i]);
}