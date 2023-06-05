/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:15:21 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/05 18:48:23 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

char	**check_input_spilt(int argc, char **argv, int *array_size)
{
	char	**str;
	int		i;

	i = 1;
	while (i < argc)
		*array_size += check_input_size(argv[i++]);
	str = input_split(argv, argc, *array_size);
	return (str);
}

int	check_input_size(char *argv)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (argv[i])
	{
		while (argv[i] && (check_input_separator(argv[i]) == 1))
			i++;
		if (argv[i] && (check_input_separator(argv[i]) == 0))
		{
			i++;
			count++;
		}
		while (argv[i] && (check_input_separator(argv[i]) == 0))
			i++;
	}
	return (count);
}

char	**input_split(char **argv, int argc, int array_size)
{
	char	**str;
	int		i;
	int		j;

	j = 0;
	i = 1;
	str = (char **)malloc(array_size * sizeof(char *) + 1);
	printf("array_size : %d\n", array_size);
	while (i < argc)
	{
		str = input_split_argv(str, *(argv + i), &j);
		i++;
	}
	str[array_size] = 0;
	return (str);
}

char	**input_split_argv(char **str, char *argv, int *two_malloc_count)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		while (argv[i] && string_check(argv[i]) == 1)
		{
			i++;
		}
		while (argv[i] && string_check(argv[i]) == 0)
		{
			str[*two_malloc_count] = ft_substr(argv, &i);
			(*two_malloc_count)++;
		}
	}
	return (str);
}

int	string_check(char s)
{
	if (s == 32)
		return (1);
	return (0);
}
