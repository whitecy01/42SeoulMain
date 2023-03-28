#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

long long	len(long long count)
{
	int	num;

	num = 0;
	if (count < 0)
	{
		num++;
		count *= -1;
	}
	else if (count == 0)
	{
		num++;
		return (num);
	}
	while (count > 0)
	{
		count = count / 10;
		num++;
	}
	return (num);
}

char	*ft_c(char *temp)
{
	temp[0] = '0';
	return (temp);
}

char	*ft_itoa(int n)
{
	long long	count;
	int			malloc_count;
	char		*temp;

	count = (long long)n;
	malloc_count = len(count);
	temp = (char *)malloc(sizeof(char) * malloc_count + 1);
	if (!temp)
		return (0);
	temp[malloc_count--] = '\0';
	if (count == 0)
		return (ft_c(temp));
	if (count < 0)
	{
		temp[0] = '-';
		count *= -1;
	}
	while (count > 0)
	{
		temp[malloc_count--] = (count % 10) + '0';
		count = count / 10;
	}
	return (temp);
}

int main()
{
	int m = OPEN_MAX;
	printf("OPEN_MAX : %d\n", m);
	int fd;
	for (int i = 1; i <= m; i++)
	{
		char *c;
		c = ft_itoa(i);
		fd = open(c, O_RDONLY);
		printf("fd : %d\n",fd);
		if (fd < 0)
			break ;
	}
	printf("OPEN_MAX : %d\n", m);

}