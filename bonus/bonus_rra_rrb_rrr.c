/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_rra_rrb_rrr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 18:23:33 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/20 16:17:26 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./head/checker.h"

void	rra(t_stack **a)
{
	t_node	*bottom_new_location;

	if (!((*a)->top->next) || !((*a)->top))
		return ;
	bottom_new_location = (*a)->bottom;
	(*a)->bottom = (*a)->bottom->prev;
	(*a)->bottom->next = NULL;
	bottom_new_location->prev = NULL;
	bottom_new_location->next = (*a)->top;
	(*a)->top->prev = bottom_new_location;
	(*a)->top = (*a)->top->prev;
}

void	rrb(t_stack **b)
{
	t_node	*bottom_new_location;

	if (!((*b)->top->next) || !((*b)->top))
		return ;
	bottom_new_location = (*b)->bottom;
	(*b)->bottom = (*b)->bottom->prev;
	(*b)->bottom->next = NULL;
	bottom_new_location->prev = NULL;
	bottom_new_location->next = (*b)->top;
	(*b)->top->prev = bottom_new_location;
	(*b)->top = (*b)->top->prev;
}

void	rrr(t_stack **a, t_stack **b)
{
	t_node	*bottom_new_location_a;
	t_node	*bottom_new_location_b;

	if (((*a)->top->next) || ((*a)->top))
	{
	bottom_new_location_a = (*a)->bottom;
	(*a)->bottom = (*a)->bottom->prev;
	(*a)->bottom->next = NULL;
	bottom_new_location_a->prev = NULL;
	bottom_new_location_a->next = (*a)->top;
	(*a)->top->prev = bottom_new_location_a;
	(*a)->top = (*a)->top->prev;
	}
	if (((*b)->top->next) || ((*b)->top))
	{
	bottom_new_location_b = (*b)->bottom;
	(*b)->bottom = (*b)->bottom->prev;
	(*b)->bottom->next = NULL;
	bottom_new_location_b->prev = NULL;
	bottom_new_location_b->next = (*b)->top;
	(*b)->top->prev = bottom_new_location_b;
	(*b)->top = (*b)->top->prev;
	}
}
