/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_changeint.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:18:20 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/05 18:48:27 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

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
	int	*temp;
	int	i;

	temp = (int *)malloc(sizeof(int) * (*array_size));
	i = 0;
	while (i < *array_size)
	{
		temp[i] = ft_atoi(array_split[i]);
		i++;
	}
	i = 0;
	*array_size = 0;
	while (temp[i])
	{
		(*array_size)++;
		i++;
	}
	return (temp);
}

int	ft_atoi(char *str)
{
	int	i;
	int	result;
	int	min;

	i = 0;
	min = 1;
	if (str[i] == 32)
		print_error(-1);
	if (str[i] == '-')
	{
		min = -1;
		i++;
	}
	result = 0;
	while (str[i])
	{
		if ('0' <= str[i] && str[i] <= '9')
			result = (10 * result) + str[i] - '0';
		else
			print_error(-1);
		i++;
	}
	return (result * min);
}
