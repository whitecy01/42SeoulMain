/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_changeint.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:18:20 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/25 20:58:00 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_input_separator(char c)
{
	if (c == 32)
		return (1);
	return (0);
}

char	*ft_substr(char *s, int *start)
{
	int		i;
	char	*temp;

	temp = (char *)malloc((sizeof(char) * ft_strlen(s, *start)) + 1);
	if (!temp)
		return (NULL);
	i = 0;
	while (s[*start] != '\0' && s[*start] != 32)
	{
		temp[i] = s[*start];
		(*start)++;
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

int	ft_strlen(const char *s, int start)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[start] != '\0' && s[start] != 32)
	{
		if (s[start] == 32)
			break ;
		start++;
		i++;
	}
	return (i);
}

int	*change_int(char **array_split, int *array_size)
{
	int		*temp;
	int		i;

	temp = (int *)malloc(sizeof(int) * (*array_size));
	i = 0;
	while (i < *array_size)
	{
		temp[i] = ft_atoi(array_split[i]);
		i++;
	}
	overlap_check(temp, (*array_size));
	return (temp);
}

int	ft_atoi(char *str)
{
	int		i;
	long	result;
	int		min;

	i = 0;
	min = 1;
	empty_string_number_check(str);
	if (str[i] == 32)
		print_error(-1);
	if (str[i] == '-')
	{
		min = -1;
		i++;
	}
	result = atoi_while((str + i));
	if (result == 0 && min == -1)
		print_error(-1);
	result = result * min;
	if (!((-2147483648 <= result) && (result <= 2147483647)))
		print_error(-1);
	return (result);
}
