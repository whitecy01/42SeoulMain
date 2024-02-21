/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_ra_rb_rr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:40:19 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/20 16:17:38 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./head/checker.h"

void	ra(t_stack **a)
{
	t_node	*top_loc;

	if (!((*a)->top->next) || !((*a)->top))
		return ;
	top_loc = (*a)->top;
	(*a)->top = (*a)->top->next;
	(*a)->top->prev = NULL;
	top_loc->next = NULL;
	(*a)->bottom->next = top_loc;
	top_loc->prev = (*a)->bottom;
	(*a)->bottom = top_loc;
}

void	rb(t_stack **b)
{
	t_node	*top_loc;

	if (!((*b)->top->next) || !((*b)->top))
		return ;
	top_loc = (*b)->top;
	(*b)->top = (*b)->top->next;
	(*b)->top->prev = NULL;
	top_loc->next = NULL;
	(*b)->bottom->next = top_loc;
	top_loc->prev = (*b)->bottom;
	(*b)->bottom = top_loc;
}

void	rr(t_stack **a, t_stack **b)
{
	t_node	*top_a;
	t_node	*top_b;

	if (((*a)->top->next) || ((*a)->top))
	{
	top_a = (*a)->top;
	(*a)->top = (*a)->top->next;
	(*a)->top->prev = NULL;
	top_a->next = NULL;
	(*a)->bottom->next = top_a;
	top_a->prev = (*a)->bottom;
	(*a)->bottom = top_a;
	}
	if (((*b)->top->next) || ((*b)->top))
	{
	top_b = (*b)->top;
	(*b)->top = (*b)->top->next;
	(*b)->top->prev = NULL;
	top_b->next = NULL;
	(*b)->bottom->next = top_b;
	top_b->prev = (*b)->bottom;
	(*b)->bottom = top_b;
	}
}
