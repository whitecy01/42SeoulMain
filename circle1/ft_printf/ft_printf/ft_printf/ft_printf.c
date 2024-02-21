/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 18:53:34 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/02 17:13:56 by jaeyojun         ###   ########seoul.kr  */
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

int	ft_printf_second(va_list vl, const char *str, int *count_num)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = 0;
	while (str[i] != '\0')
	{
		tmp = 0;
		if (str[i] == '%')
			tmp = check_percent(str, i++, vl);
		else
		{
			if (write(1, &str[i], 1) == -1)
				return (*count_num = -1);
			tmp++;
		}
		if (tmp == -1)
		{
			*count_num = tmp;
			break ;
		}
		*count_num += tmp;
		i++;
	}
	return (*count_num);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		count_num;
	va_list	vl;

	i = 0;
	count_num = 0;
	va_start(vl, str);
	ft_printf_second(vl, str, &count_num);
	va_end(vl);
	return (count_num);
}

