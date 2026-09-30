/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:00:09 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/05/18 16:12:43 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	output_int_3(int *len)
{
	if (write(1, "-2147483648", 11) == -1)
		return (*len = -1);
	return (*len = 11);
}

int	output_int_2(int output, int *len)
{
	char	math;

	if (output == -2147483648)
		return (output_int_3(len));
	else if (output < 0)
	{
		if (write(1, "-", 1) == -1)
			return (*len = -1);
		output *= -1;
		(*len)++;
		output_int_2(output, len);
	}
	else
	{
		if (output <= 0)
			return (0);
		if (output_int_2(output / 10, len) == -1)
			return (-1);
		(*len)++;
		math = output % 10 + '0';
		if (write(1, &math, 1) == -1)
			return (*len = -1);
	}
	return (*len);
}

int	output_int(va_list vl)
{
	int			output;
	int			len;

	len = 0;
	output = va_arg(vl, int);
	if (output == 0)
	{
		if (write (1, "0", 1) == -1)
			return (-1);
		len++;
		return (len);
	}
	output_int_2(output, &len);
	if (len == -1)
		return (-1);
	return (len);
}
