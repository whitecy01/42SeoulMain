/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ra_rb_rr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:40:19 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/26 14:28:24 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra(t_stack **a)
{
	t_node	*top_loc;

	if (((*a)->top->next) && ((*a)->top))
	{
		top_loc = (*a)->top;
		(*a)->top = (*a)->top->next;
		(*a)->top->prev = NULL;
		top_loc->next = NULL;
		(*a)->bottom->next = top_loc;
		top_loc->prev = (*a)->bottom;
		(*a)->bottom = top_loc;
	}
	write(1, "ra\n", 3);
}

void	rb(t_stack **b)
{
	t_node	*top_loc;

	if (((*b)->top->next) && ((*b)->top))
	{
		top_loc = (*b)->top;
		(*b)->top = (*b)->top->next;
		(*b)->top->prev = NULL;
		top_loc->next = NULL;
		(*b)->bottom->next = top_loc;
		top_loc->prev = (*b)->bottom;
		(*b)->bottom = top_loc;
	}
	write(1, "rb\n", 3);
}

void	rr(t_stack **a, t_stack **b)
{
	t_node	*top_a;
	t_node	*top_b;

	if (((*a)->top->next) && ((*a)->top))
	{
		top_a = (*a)->top;
		(*a)->top = (*a)->top->next;
		(*a)->top->prev = NULL;
		top_a->next = NULL;
		(*a)->bottom->next = top_a;
		top_a->prev = (*a)->bottom;
		(*a)->bottom = top_a;
	}
	if (((*b)->top->next) && ((*b)->top))
	{
		top_b = (*b)->top;
		(*b)->top = (*b)->top->next;
		(*b)->top->prev = NULL;
		top_b->next = NULL;
		(*b)->bottom->next = top_b;
		top_b->prev = (*b)->bottom;
		(*b)->bottom = top_b;
	}
	write(1, "rr\n", 3);
}
