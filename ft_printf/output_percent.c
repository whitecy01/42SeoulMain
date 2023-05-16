/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_percent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:00:09 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/05/16 14:28:14 by jaeyojun         ###   ########seoul.kr  */
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
	write(1, &alp, 1);
	len++;
	return (len);
}

//'s'
int	output_string(va_list vl)
{
	char	*string;
	int		len;

	len = 0;
	string = va_arg(vl, char *);
	while(string[len])
	{
		write(1, &string[len], 1);
		len++;
	}
	len--;
	return (len);
}



//'p'
void output_address_2(unsigned long long output)
{

	if (output > 0)
	{
		output_address_2(output / 16);
		if (output / 16 <= 0)
			return ;
		write(1, &"0123456789abcdef"[output / 16], 1);
		write(1, &"0123456789abcdef"[output % 16], 1);
	}
}

//len 수정
int	output_address(va_list vl)
{
	unsigned long long	output;
	int					len;

	len = 0;
	output = (unsigned long long)va_arg(vl, void *);
	//printf("%llu\n", output);
	write(1, "Ox" , 2);
	output_address_2(output);
	return (len);
}

//'d'
int	output_int(va_list vl)
{
	int		output;
	int		len;

	len = 0;
	output = va_arg(vl, int);
	while (output > 0)
	{
		output = output / 10;
		len++;
	}
	return (len);
}


//'u'
void output_unsignedint2(unsigned int output)
{
	char	one_output_char;

	if(output > 0)
	{
		output_unsignedint2(output / 10);
		one_output_char = (output % 10) + '0';
		write(1, &one_output_char, 1);
	}
	//printf("%d", len); 
}


int	output_unsignedint(va_list vl)
{
	unsigned int	output;
	int				len;
	char			output_char;

	len = 0;
	output = va_arg(vl, unsigned int);
	//값 출력
	if (output == 0)
	{
		output_char = output + '0';
		write(1, &output_char, 1);
		len++;
		return (len);
	}
	output_unsignedint2(output);
	//길이 세어주기
	while(output > 0)
	{
		output = output / 10;
		len++;
	}
	return (len);
}




//'16진수', len 수정
void output_six_smlletter(unsigned int output)
{
	if (output > 0)
	{
		output_six_smlletter(output / 16);
		write(1, &"0123456789abcdef"[output % 16], 1);
	}
}

void output_six_bigletter(unsigned int output)
{
	if (output > 0)
	{
		output_six_bigletter(output / 16);
		//printf("output : %d\n", output);
		// write(1, &"0123456789ABCDEF"[output / 16], 1);
		write(1, &"0123456789ABCDEF"[output % 16], 1);
	}
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
		write(1, &output_char, 1);
		len++;
		return (len);
	}
	if (check == 'x')
		output_six_smlletter(output);
	else if (check == 'X')
		output_six_bigletter(output);
	return (len);
}

//%% 이거는 사용할 필요가 없음
int	output_percent(va_list vl)
{
	char			output_char;
	int				len;

	len = 0;
	//output = (unsigned int)va_arg(vl, unsigned int);
	write(1, "%%", 1);
	return (len);
}



