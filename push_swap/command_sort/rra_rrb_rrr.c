/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rra_rrb_rrr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 18:23:33 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/09 20:30:03 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../head/push_swap.h"

void	rra(t_stack **a)
{
	t_node	*bottom_new_location;

	bottom_new_location = (*a)->bottom;
	(*a)->bottom = (*a)->bottom->prev;
	bottom_new_location->next = (*a)->top;
	(*a)->top->prev = bottom_new_location;
	(*a)->top = (*a)->top->next;
}

void	rrb(t_stack **b)
{
	t_node	*bottom_new_location;

	bottom_new_location = (*b)->bottom;
	(*b)->bottom = (*b)->bottom->prev;
	bottom_new_location->next = (*b)->top;
	(*b)->top->prev = bottom_new_location;
	(*b)->top = (*b)->top->next;
}

void	rrr(t_stack **a, t_stack **b)
{
	rra(a);
	rrb(b);
}
