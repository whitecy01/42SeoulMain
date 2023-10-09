/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_xu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:00:34 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/05/18 16:13:03 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	output_unsignedint2(unsigned int output, int *len)
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

int	output_six_smlletter(unsigned int output, int *len)
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

int	output_six_bigletter(unsigned int output, int *len)
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
