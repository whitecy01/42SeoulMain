/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_csp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:58:53 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/05/19 14:21:24 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	output_char(va_list vl)
{
	char	alp;
	int		len;

	len = 0;
	alp = va_arg(vl, int);
	if (write(1, &alp, 1) == -1)
		return (-1);
	len++;
	return (len);
}

int	output_string(va_list vl)
{
	char	*string;
	int		len;

	len = 0;
	string = (char *)va_arg(vl, void *);
	if (string == NULL)
	{
		if (write (1, "(null)", 6) == -1)
			return (-1);
		return (6);
	}
	while (string[len])
	{
		if (write(1, &string[len], 1) == -1)
			return (-1);
		len++;
	}
	return (len);
}

int	output_address_2(unsigned int output, int *len)
{
	int	check;

	check = 0;
	if (output > 0)
	{
		output_address_2(output / 16, len);
		check = write(1, &"0123456789abcdef"[output % 16], 1);
		(*len)++;
		if (check == -1)
		{
			*len = check;
			return (*len);
		}
	}
	return (*len);
}

int	output_address(va_list vl)
{
	unsigned int	output;
	int					len;

	len = 2;
	output = (unsigned int)va_arg(vl, void *);
	if (output == 0)
	{
		if (write(1, "0x0", 3) == -1)
			return (-1);
		return (++len);
	}
	if (write(1, "0x", 2) == -1)
		return (-1);
	output_address_2(output, &len);
	return (len);
}
