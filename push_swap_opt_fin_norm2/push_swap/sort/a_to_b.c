/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_to_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 06:54:49 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/18 19:51:31 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../head/push_swap.h"

void	ra_rb_pb_while(t_stack **a, t_stack **b, int array_size, int *count)
{
	int	pivot1;
	int	pivot2;
	int	turn;

	pivot1 = pivot_answer(a, array_size);
	pivot2 = pivot_answer2(a, array_size);
	turn = -1;
	while (++turn < array_size)
	{
		if ((*a)->top->content >= pivot1)
			sort_alogorithm_ra(a, &count[0]);
		else
		{
			sort_alogorithm_pb(a, b, &count[1]);
			if ((*b)->top->content > pivot2)
			{
				if ((*a)->top != NULL && ((*a)->top->content >= pivot1)
					&& turn + 1 < array_size)
					one_plus_one_rr(a, b, &count[0], &turn);
				else
					rb(b);
				count[2]++;
			}
		}
	}
}	


void	a_to_b(t_stack **a, t_stack **b, int array_size)
{
	int	turn;
	int count[3]; // count[0] == ra_count count[1] == pb_count, count[2] == rb_count;
	int stack_a_count;

	if (check_sorted((*a)->top, array_size, A))
		return ;
	stack_a_count = stack_top_count(a);
	if (array_size <= 3)
		return (three_underonly_fuc_a(a, array_size));
	reset_count_array(count);
	ra_rb_pb_while(a, b, array_size, count);
	turn = 0;
	if ((stack_a_count != array_size))
		turn = ra_rb_sum_rrr(count[0], count[2], a, b);
	rrb_a_to_b(count[2], b, turn);
	while (turn < count[0])
	{
		if (stack_a_count != array_size)
			rra(a);
		turn++;
	}
	a_to_b(a, b, count[0]);
	b_to_a(a, b, count[2]);
	b_to_a(a, b, count[1] - count[2]);
}
