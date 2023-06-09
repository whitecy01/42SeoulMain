/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ra_rb_rr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:40:19 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/09 20:31:39 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../head/push_swap.h"

void	ra(t_stack **a)
{
	(*a)->top = (*a)->top->next;
	(*a)->bottom = (*a)->bottom->next;
}

void	rb(t_stack **b)
{
	(*b)->top = (*b)->top->next;
	(*b)->bottom = (*b)->bottom->next;
}

void	rr(t_stack **a, t_stack **b)
{
	ra(a);
	rb(b);
}
