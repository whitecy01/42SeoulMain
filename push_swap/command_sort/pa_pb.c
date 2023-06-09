/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_pb.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:37:13 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/09 17:42:45 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../head/push_swap.h"

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
		while (location)
			location = location->next;
		location->next = new;
		new->prev = location;
		(*b)->bottom = new;
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
	(*a)->top->prev = NULL;
	free(change);
	(*a)->bottom->next = (*a)->top;
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
		while (location)
			location = location->next;
		location->next = new;
		new->prev = location;
		(*a)->bottom = new;
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
	(*b)->top->prev = NULL;
	free(change);
	(*b)->bottom->next = (*b)->top;
}
