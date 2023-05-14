/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 18:53:34 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/05/14 21:07:50 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include <stdio.h>
#include <unistd.h>

void	output_char(va_list vl)
{
	char	alp;

	alp = va_arg(vl, int);
	write(1, &alp, 1);
}



void	check_percent(const char *str, int i, va_list vl)
{
	i++;
	if (str[i] == 'c')
		output_char(vl);
	// else if (str[i] == 's')
	// else if (str[i] == 'p')
	// else if (str[i] == 'd')
	// else if (str[i] == 'i')
	// else if (str[i] == 'u')
	// else if (str[i] == 'x')
	// else if (str[i] == 'X')
	// else if (str[i] == '%')
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
			check_percent(str, i, vl);
			count_num++;
		}
		i++;
	}
	va_end(vl);
	return (i);
}

int main()
{
	char a = 'a';
	int num = ft_printf("  %c", a);
	printf("\n%d", num);
}


