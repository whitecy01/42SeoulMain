/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minslee <minslee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 19:34:13 by minslee           #+#    #+#             */
/*   Updated: 2022/06/23 19:34:49 by minslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_str(char **str, int row)
{
	int	index;

	index = 0;
	while (index < row)
		free(str[index++]);
	free(str);
}

static int	get_split_size(const char *str, int index)
{
	int	i;

	i = index;
	while (str[index] != '\0' && str[index] != ' ')
		index++;
	return (index);
}

static int	get_whole_size(const char *str)
{
	int	index;
	int	size;

	size = 0;
	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] == ' ')
			index++;
		else
		{
			while (str[index] != ' ' && str[index] != '\0')
				index++;
			size++;
		}
	}
	return (size);
}

static int	get_split(const char *str, char **res, int row, int *index)
{
	int	col;

	col = 0;
	res[row] = (char *)malloc(sizeof(char) * \
		(get_split_size(str, (*index)) + 1));
	if (str[row] == 0)
	{
		free_str(res, row);
		return (0);
	}
	col = 0;
	while (str[(*index)] != ' ' && str[(*index)] != '\0')
		res[row][col++] = str[(*index)++];
	return (1);
}

char	**ft_split(const char *str)
{
	int		index;
	int		row;
	char	**res;

	row = 0;
	index = 0;
	res = (char **)malloc(sizeof(char *) * (get_whole_size(str) + 1));
	while (str[index] != '\0')
	{
		if (str[index] == ' ')
			index++;
		else
		{
			if (get_split(str, res, row, &index) == 0)
				return (0);
			row++;
		}
	}
	res[row] = NULL;
	return (res);
}
