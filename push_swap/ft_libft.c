/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minslee <minslee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 19:34:13 by minslee           #+#    #+#             */
/*   Updated: 2022/06/23 19:34:49 by minslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	is_space(char c)
{
	if (c == '\n' || c == '\t' || c == '\r')
		return (1);
	else if (c == '\v' || c == '\f' || c == ' ')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	long long	num;
	int			neg;
	long long	tmp;

	neg = 1;
	num = 0;
	while (is_space(*str))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			neg = -1;
	while (*str >= '0' && *str <= '9')
	{
		if (num > INT_MAX || num < INT_MIN)
			exit(write(1, "Error\n", 6) || 1);
		tmp = num;
		num = num * 10 + *str++ - '0';
		if ((neg * num) < tmp && neg == 1)
			return (0);
		if ((neg * num) > tmp && neg == -1)
			return (0);
	}
	return ((int)(num * neg));
}

int	ft_strlen(const char *str)
{
	int	index;

	index = 0;
	while (str[index] != '\0')
		index++;
	return (index);
}

int	if_in_space(char *str)
{
	char	*tmp;

	tmp = str;
	while ((*tmp) != '\0')
	{
		if ((*tmp) == ' ')
			return (1);
		tmp++;
	}
	return (0);
}

int	is_all_digit(char *str)
{
	char	*tmp;

	tmp = str;
	while ((*tmp) != '\0')
	{
		if ((*tmp) < '0' && (*tmp) > '9')
			return (0);
		tmp++;
	}
	return (1);
}
