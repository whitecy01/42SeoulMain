/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_pb.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:37:13 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/22 19:02:32 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_b(t_stack **b, t_node *change)
{
	t_node	*new;
	t_node	*location;

	new = create_node(change->content);
	if (!((*b)->top))
	{
		(*b)->top = new;
		(*b)->bottom = (*b)->top;
	}
	else
	{
		location = (*b)->top;
		location->prev = new;
		new->next = (*b)->top;
		(*b)->top = (*b)->top->prev;
	}
}

void	pb(t_stack **a, t_stack **b)
{
	t_node	*change;

	if (!((*a)->top))
		return ;
	change = (*a)->top;
	(*a)->top = (*a)->top->next;
	push_b(b, change);
	if (((*a)->top))
		(*a)->top->prev = NULL;
	if (!((*a)->top))
		(*a)->bottom = NULL;
	free(change);
	write(1, "pb\n", 3);
}

void	push_a(t_stack **a, t_node *change)
{
	t_node	*new;
	t_node	*location;

	new = create_node(change->content);
	if (!((*a)->top))
	{
		(*a)->top = new;
		(*a)->bottom = (*a)->top;
	}
	else
	{
		location = (*a)->top;
		location->prev = new;
		new->next = (*a)->top;
		(*a)->top = (*a)->top->prev;
	}
}

void	pa(t_stack **a, t_stack **b)
{
	t_node	*change;

	if (!((*b)->top))
		return ;
	change = (*b)->top;
	(*b)->top = (*b)->top->next;
	push_a(a, change);
	if (((*b)->top))
		(*b)->top->prev = NULL;
	if (!((*b)->top))
		(*b)->bottom = NULL;
	free(change);
	write(1, "pa\n", 3);
}
