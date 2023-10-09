#include <ctype.h>  // C++ 에서는 <cctype>

int ft_atoi(char s[]) {
  int i, n, sign;
  for (i = 0; isspace(s[i]); i++)
    ; /* skip white space */
  sign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '+' || s[i] == '-') /* skip sign */
    i++;
  for (n = 0; isdigit(s[i]); i++) n = 10 * n + (s[i] - '0');
  return sign * n;
}


int	ftt_atoi(const char *string)
{
	int		i;
	long	sr;
	long	result;
	long 	tmp = 0;

	result = 0;
	sr = 1;
	i = 0;
	while (string[i] != '\0' && ((string[i] >= 9 && string[i] <= 13)
			|| string[i] == 32))
		i++;
	if (string[i] == '-')
	{
		sr *= -1;
		i++;
	}
	else if (string[i] == '+')
		i++;
	while (string[i] != '\0' && (string[i] >= '0' && string[i] <= '9'))
	{
		result = result * 10 + (string[i] - '0');
		if (sr > 0 && result < tmp){
			return -1;
		}else if(sr < 0 && result > tmp){
			return -1;
		}
		tmp = result;
		i++;
	}
	return ((int)(result * sr));
}

#include <stdio.h>
#include <stdlib.h>
int main()
{//27670116210564327421
	printf("ft_atoi: %d\n", ft_atoi("922337203685477580"));
	printf("atoi: %d\n",	atoi("922337203685477580"));
	printf("ftt_atoi: %d\n",	ftt_atoi("922337203685477580"));
}