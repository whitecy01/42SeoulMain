/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_to_b2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:51:07 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/22 19:01:50 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	one_plus_one_rr(t_stack **a, t_stack **b, int *ra_count, int *turn)
{
	rr(a, b);
	(*ra_count)++;
	(*turn)++;
}

int	ra_rb_sum_rrr(int ra_count, int rb_count, t_stack **a, t_stack **b)
{
	int	turn;

	turn = 0;
	while (turn < rb_count && turn < ra_count)
	{
		rrr(a, b);
		turn++;
	}
	return (turn);
}

void	rrb_a_to_b(int rb_count, t_stack **b, int turn)
{
	while (turn < rb_count)
	{
		if (turn < rb_count)
			rrb(b);
		turn++;
	}
}

void	rra_a_to_b(int ra_count, t_stack **a, int turn, int array_size)
{
	int	stack_a_count;

	stack_a_count = stack_top_count(a);
	while (turn < ra_count)
	{
		if (stack_a_count != array_size)
		{
			if (turn < ra_count)
				rra(a);
		}
		turn++;
	}
}

void	reset_count_array(int *count)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		count[i] = 0;
		i++;
	}
}
