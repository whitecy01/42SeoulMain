/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_two_three.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minslee <minslee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 19:34:13 by minslee           #+#    #+#             */
/*   Updated: 2022/06/23 19:34:49 by minslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	if_case_two(t_stack *st, int a_b, int sort)
{
	if (sort == 1)
	{
		if (st->lst->data > st->lst->next->data)
		{
			if (a_b == 0)
				swap(&st, "sa\n");
			else if (a_b == 1)
				swap(&st, "sb\n");
		}
	}
	else
	{
		if (st->lst->data < st->lst->next->data)
		{
			if (a_b == 0)
				swap(&st, "sa\n");
			else if (a_b == 1)
				swap(&st, "sb\n");
		}
	}
}

static void	sort_three(t_stack *a, int max_index, int min_index)
{
	if (min_index == 1 && max_index == 0)
		rotate(&a, "ra\n");
	else if (min_index == 2 && max_index == 0)
	{
		swap(&a, "sa\n");
		r_rotate(&a, "rra\n");
	}
	else if (min_index == 0 && max_index == 1)
	{
		r_rotate(&a, "rra\n");
		swap(&a, "sa\n");
	}
	else if (min_index == 2 && max_index == 1)
		r_rotate(&a, "rra\n");
	else if (min_index == 1 && max_index == 2)
		swap(&a, "sa\n");
}

void	if_case_three(t_stack *a, int step)
{
	int	tmp[3];
	int	index;
	int	max_index;
	int	min_index;

	index = 0;
	tmp[0] = a->lst->data;
	tmp[1] = a->lst->next->data;
	tmp[2] = a->lst->next->next->data;
	while (index < 3)
	{
		if (tmp[index] == (3 + step))
			max_index = index;
		if (tmp[index] == (1 + step))
			min_index = index;
		index++;
	}
	sort_three(a, max_index, min_index);
}
