/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_percent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:00:09 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/05/17 18:24:40 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//'c'
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

//'s'
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

//'p' ////////////////////
int	output_address_2(unsigned long long output, int *len)
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
	unsigned long long	output;
	int					len;

	len = 2;
	output = (unsigned long long)va_arg(vl, void *);
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
/////////////////////////////


//'d' 'i'
int	output_int_2(int output, int *len)
{
	char	math;

	if (*len == -1)
		return (-1);
	if (output == -2147483648)
	{
		if (write(1, "-2147483648", 11) == -1)
			return (*len = -1);
		return ((*len) = 11);
	}
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
//////////////////////////

//'u'
int output_unsignedint2(unsigned int output, int *len)
{
	char	one_output_char;

	if (*len == -1)
		return (-1);
	if (output > 0)
	{
		if (output_unsignedint2(output / 10, len) == -1)
			return (*len = -1);
		(*len)++;
		one_output_char = (output % 10) + '0';
		if (write(1, &one_output_char, 1) == -1)
			return (*len = -1);
	}
	return (*len);
}

int	output_unsignedint(va_list vl)
{
	unsigned int	output;
	int				len;
	char			output_char;

	len = 0;
	output = va_arg(vl, unsigned int);
	if (output == 0)
	{
		output_char = output + '0';
		if (write(1, &output_char, 1) == -1)
			return (-1);
		len++;
		return (len);
	}
	output_unsignedint2(output, &len);
	if (len == -1)
		return (-1);
	return (len);
}

//'x' 'X'
int output_six_smlletter(unsigned int output, int *len)
{
	if (output > 0)
	{
		if (output_six_smlletter(output / 16, len) == -1)
			return (*len = -1);
		if (write(1, &"0123456789abcdef"[output % 16], 1) == -1)
			return (*len = -1);
		(*len)++;
	}
	return (*len);
}

int output_six_bigletter(unsigned int output, int *len)
{
	if (output > 0)
	{
		if (output_six_bigletter(output / 16, len) == -1)
			return (*len = -1);
		if (write(1, &"0123456789ABCDEF"[output % 16], 1) == -1)
			return (*len = -1);
		(*len)++;
	}
	return (*len);
}

int	output_six(va_list vl, char check)
{
	unsigned int	output;
	char			output_char;
	int				len;

	len = 0;
	output = (unsigned int)va_arg(vl, unsigned int);
	if (output == 0)
	{
		output_char = output + '0';
		if (write(1, &output_char, 1) == -1)
			return (-1);
		len++;
		return (len);
	}
	if (check == 'x')
		output_six_smlletter(output, &len);
	else if (check == 'X')
		output_six_bigletter(output, &len);
	return (len);
}

