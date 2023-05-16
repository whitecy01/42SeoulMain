/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 18:53:34 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/05/16 14:24:59 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_percent(const char *str, int i, va_list vl)
{
	i++;
	int len;
	
	len = 0;
	if (str[i] == 'c')
		len = output_char(vl);
	else if (str[i] == 's')
		len = output_string(vl);
	else if (str[i] == 'p')
		len = output_address(vl);
	else if (str[i] == 'd' || str[i] == 'i')
		len = output_int(vl);
	else if (str[i] == 'u')
		len = output_unsignedint(vl);
	// else if (str[i] == 'x')
	// else if (str[i] == 'X')
	// else if (str[i] == '%')
	return (len);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		count_num;
	va_list	vl;

	count_num = 0;
	i = 0;
	va_start(vl, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			count_num += check_percent(str, i, vl);
			i++;
		}
		else
		{
			write(1, &str[i], 1);
			count_num++;
		}
		if (count_num == -1)
			break ;
		i++;
	}
	va_end(vl);
	return (count_num);
}

int main()
{
	//char a = 'a';
	// char *sec = "aaaa";
	// printf("printf : %p awd\n", sec);
	// int num = ft_printf("ft_printf : %p awd", sec);
	// num = 0;
	unsigned int s = -2;
	int num = ft_printf("ft_printf : %u", s);
	num = 0;
	

	//printf("\n num : %d", num);
	
	//주소값
	// printf("\n");
	// printf("49606562: %d, ", 49606562 / 16);
	// printf("%d\n", 49606562 % 16);
	// printf("3100410: %d, ", 3100410 / 16);
	// printf("%d\n", 3100410 % 16);
	// printf("193775: %d, ", 193775 / 16);
	// printf("%d\n", 193775 % 16);
	// printf("12110: %d, ", 12110 / 16);
	// printf("%d\n", 12110 % 16);
	// printf("756: %d, ", 756 / 16);
	// printf("%d\n", 756 % 16);
	// printf("47: %d, ", 47 / 16);
	// printf("%d\n", 47 % 16);
	// printf("2: %d, ", 2 / 16);
	// printf("%d\n", 2 % 16);
	
	//16진수 
	// printf("\n");
	// printf("49606562: %d, ", 49606562 / 16);
	// printf("%d\n", 49606562 % 16);
	// printf("3100410: %d, ", 3100410 / 16);
	// printf("%d\n", 3100410 % 16);
	// printf("193775: %d, ", 193775 / 16);
	// printf("%d\n", 193775 % 16);
	// printf("12110: %d, ", 12110 / 16);
	// printf("%d\n", 12110 % 16);
	// printf("756: %d, ", 756 / 16);
	// printf("%d\n", 756 % 16);
	// printf("47: %d, ", 47 / 16);
	// printf("%d\n", 47 % 16);
	// printf("2: %d, ", 2 / 16);
	// printf("%d\n", 2 % 16);
}


