#include <stdio.h>


void mult()
{
	static int count = 1;// static 지역 변수에 선언
	count = count * 2;
	printf("mult count 값 : %d\n", count);
}

int main()
{
	for (int i = 0; i < 4; i++)
	{
		mult();
	}

}