/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_four_five.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minslee <minslee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 19:34:13 by minslee           #+#    #+#             */
/*   Updated: 2022/06/23 19:34:49 by minslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_index(t_stack *a, int data)
{
	t_list	*tmp;
	int		index;

	index = 0;
	tmp = a->lst;
	while (tmp != NULL)
	{
		if (tmp->data == data)
			return (index);
		tmp = tmp->next;
		index++;
	}
	return (-1);
}

void	if_case_four(t_stack *a, t_stack *b)
{
	int	index;

	index = get_index(a, 1);
	if (index < (a->len) / 2)
		while (a->lst->data != 1)
			rotate(&a, "ra\n");
	else
		while (a->lst->data != 1)
			r_rotate(&a, "rra\n");
	push(&a, &b, "pb\n");
	if_case_three(a, 1);
	push(&b, &a, "pa\n");
}

void	if_case_five(t_stack *a, t_stack *b)
{
	while (a->len > 3)
	{
		if (a->lst->data == 1)
			push(&a, &b, "pb\n");
		else if (a->lst->data == 2)
			push(&a, &b, "pb\n");
		else
			rotate(&a, "ra\n");
	}
	if_case_two(b, 1, 0);
	if_case_three(a, 2);
	push(&b, &a, "pa\n");
	push(&b, &a, "pa\n");
}
