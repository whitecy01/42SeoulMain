/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_to_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 06:55:11 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/18 06:55:38 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../head/push_swap.h"

void	b_to_a(t_stack **a, t_stack **b, int array_size)
{
	int	pivot1;
	int	pivot2;
	int	turn;
	int	rb_count = 0;
	int	ra_count = 0;
	int	pa_count = 0;
	int stack_b_count;

	(*a)->flag = 0;
	if (check_sorted((*b)->top, array_size, B))
	{
		while (array_size-- > 0)
			pa(a, b);
		return ;
	}
	stack_b_count = stack_top_count(b);
	if (array_size <= 3)
	{
		if (stack_b_count == array_size)
		{
			three_only_b(b, array_size);
			while (array_size-- > 0)
				pa(a, b);
		}
		else
		{
			under_three_b(b, array_size);
			while (array_size-- > 0)
				pa(a, b);
		}
		return ;
	}
	pivot1 = pivot_answer(b, array_size);
	pivot2 = pivot_answer2(b, array_size);
	turn = 0;
	while (turn < array_size)
	{
		if ((*b)->top->content < pivot2)
		{
			rb(b);
			rb_count++;
		}
		else
		{
			pa(a, b);
			pa_count++;
			if ((*a)->top->content < pivot1)
			{
				if ((*b)->top != NULL && ((*b)->top->content < pivot2)
					&& turn + 1 < array_size)
				{
					rr(a, b);
					rb_count++;
					turn++;
				}
				else
					ra(a);
				ra_count++;
			}
		}
		turn++;
	}
	a_to_b(a, b, pa_count - ra_count);
	turn = -1;
	while (++turn < ra_count)
		rra(a);
	a_to_b(a, b, ra_count);
	turn = -1;
	while (++turn < rb_count)
		rrb(b);
	b_to_a(a, b, rb_count);
}
