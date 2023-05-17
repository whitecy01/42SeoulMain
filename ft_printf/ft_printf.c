/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 18:53:34 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/05/17 18:04:46 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_percent(const char *str, int i, va_list vl)
{
	int	len;

	i++;
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
	else if (str[i] == 'x' || str[i] == 'X')
		len = output_six(vl, str[i]);
	else if (str[i] == '%')
	{
		if (write(1, "%%", 1) == -1)
			return (-1);
		len = 1;
	}
	return (len);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		count_num;
	va_list	vl;
	int		tmp;

	i = 0;
	count_num = 0;
	va_start(vl, str);
	while (str[i] != '\0')
	{
		tmp = 0;
		if (str[i] == '%')
		{
			tmp = check_percent(str, i, vl);
			i++;
		}
		else
		{
			if (write(1, &str[i], 1) == -1)
				return (-1);
			tmp++;
		}
		if (tmp == -1)
		{
			count_num = tmp;
			break ;
		}
		count_num += tmp;
		i++;
	}
	va_end(vl);
	return (count_num);
}


// int main()
// {
// 	//test
// 	// int num1 = printf(" %c %c %c \n", 0, '1', '2');
// 	// int num2 = ft_printf(" %c %c %c \n", 0, '1', '2');
// 	// printf("num1 : %d, num2 : %d", num1, num2);
	
// // 	//c //////
// // 	// char a = 'c';
// // 	// int num1 = printf("%c\n", a);
// // 	// int num2 = ft_printf("%c\n", a);
// // 	// printf("num1 : %d, num2: %d", num1, num2);
// // 	//////////
	

// 	//s
// 	//char *a = "awd";
// 	int num1 = printf("%s\n", (char *)NULL);
// 	int num2 = ft_printf("%s\n", (char *)NULL);
// 	printf("num1 : %d, num2: %d", num1, num2);

// 	//p
// 	//char a = 'a';
// 	//char *sec = &a;
// 	// int num1 = printf("%p\n", NULL);
// 	// int num2 = ft_printf("%p\n", NULL);
// 	//printf("num1 : %d, num2: %d", num1, num2);
	
	
// // 	//d
// // 	// int a = 214748367;
// // 	// int num1 = printf("%d\n", a);
// // 	// int num2 = ft_printf("%d\n", a);
// // 	// printf("num1 : %d, num2: %d", num1, num2);
	
// // 	//i
// // 	// int a = 34;
// // 	// int num1 = printf("%i\n", a);
// // 	// int num2 = ft_printf("%i\n", a);
// // 	// printf("num1 : %d, num2: %d", num1, num2);
	
// // 	//u
// // 	// unsigned int a = 0;
// // 	// int num1 = printf("%u\n", a);
// // 	// int num2 = ft_printf("%u\n", a);
// // 	// printf("num1 : %d, num2: %d", num1, num2);
	
// // 	//x
// // 	// int a = 34;
// // 	// int num1 = printf("%x\n", a);
// // 	// int num2 = ft_printf("%x\n", a);
// // 	// printf("num1 : %d, num2: %d", num1, num2);
	
// // 	//X
// // 	// int a = 4444;
// // 	// int num1 = printf("%X\n", a);
// // 	// int num2 = ft_printf("%X\n", a);
// // 	// printf("num1 : %d, num2: %d", num1, num2);

// // 	// printf("300: %d\n", 300 / 16);
// // 	// printf("300 나머지 : %d\n", 300 % 16);
// // 	// printf("18: %d\n", 18 / 16);
// // 	// printf("18 나머지 : %d\n", 18 % 16);
// // 	// printf("1: %d\n", 1 / 16);
// // 	// printf("1 나머지: %d", 1 % 16);

// // 	//printf("\n num : %d", num);
	
// // 	//주소값
// // 	// printf("\n");
// // 	// printf("49606562: %d, ", 49606562 / 16);
// // 	// printf("%d\n", 49606562 % 16);
// // 	// printf("3100410: %d, ", 3100410 / 16);
// // 	// printf("%d\n", 3100410 % 16);
// // 	// printf("193775: %d, ", 193775 / 16);
// // 	// printf("%d\n", 193775 % 16);
// // 	// printf("12110: %d, ", 12110 / 16);
// // 	// printf("%d\n", 12110 % 16);
// // 	// printf("756: %d, ", 756 / 16);
// // 	// printf("%d\n", 756 % 16);
// // 	// printf("47: %d, ", 47 / 16);
// // 	// printf("%d\n", 47 % 16);
// // 	// printf("2: %d, ", 2 / 16);
// // 	// printf("%d\n", 2 % 16);
	
// // 	//16진수 
// // 	// printf("\n");
// // 	// printf("49606562: %d, ", 49606562 / 16);
// // 	// printf("%d\n", 49606562 % 16);
// // 	// printf("3100410: %d, ", 3100410 / 16);
// // 	// printf("%d\n", 3100410 % 16);
// // 	// printf("193775: %d, ", 193775 / 16);
// // 	// printf("%d\n", 193775 % 16);
// // 	// printf("12110: %d, ", 12110 / 16);
// // 	// printf("%d\n", 12110 % 16);
// // 	// printf("756: %d, ", 756 / 16);
// // 	// printf("%d\n", 756 % 16);
// // 	// printf("47: %d, ", 47 / 16);
// // 	// printf("%d\n", 47 % 16);
// // 	// printf("2: %d, ", 2 / 16);
// // 	// printf("%d\n", 2 % 16);
// }


