/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minslee <minslee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 19:34:13 by minslee           #+#    #+#             */
/*   Updated: 2022/06/23 19:34:49 by minslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	init_tmp(int *tmp, int *tmp_sort, t_stack *st, int len)
{
	int		index;
	t_list	*tmp_lst;

	index = 0;
	tmp_lst = st->lst;
	while (index < len)
	{
		tmp[index] = tmp_lst->data;
		tmp_sort[index++] = tmp_lst->data;
		tmp_lst = tmp_lst->next;
	}
}

static int	get_sorted_index(int *tmp_sorted, int data, int len)
{
	int	index;

	index = 0;
	while (index < len)
	{
		if (tmp_sorted[index] == data)
			return (index + 1);
		index++;
	}
	return (-1);
}

static void	swap_array(int *lst, int a, int b)
{
	int	tmp;

	tmp = lst[a];
	lst[a] = lst[b];
	lst[b] = tmp;
}

static void	quick_sort(int *data, int start, int end)
{
	int	key;
	int	i;
	int	j;

	if (start >= end)
		return ;
	key = start;
	i = start + 1;
	j = end;
	while (i <= j)
	{
		while (i <= end && data[i] <= data[key])
			i++;
		while (j > start && data[j] >= data[key])
			j--;
		if (i > j)
			swap_array(data, j, key);
		else
			swap_array(data, i, j);
	}
	quick_sort(data, start, j - 1);
	quick_sort(data, j + 1, end);
}

void	numbering_stack(t_stack *st)
{
	int		*tmp;
	int		*tmp_sort;
	int		index;
	t_list	*tmp_lst;

	tmp = (int *)malloc(sizeof(int) * st->len);
	tmp_sort = (int *)malloc(sizeof(int) * st->len);
	init_tmp(tmp, tmp_sort, st, st->len);
	quick_sort(tmp_sort, 0, st->len - 1);
	index = 0;
	tmp_lst = st->lst;
	while (index < st->len)
	{
		tmp_lst->data = get_sorted_index(tmp_sort, tmp[index++], st->len);
		tmp_lst = tmp_lst->next;
	}
	free(tmp);
	tmp = NULL;
	free(tmp_sort);
	tmp_sort = NULL;
}
