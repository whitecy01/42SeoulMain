/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_to_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 06:55:11 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/25 15:18:16 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra_rb_pb_while_b(t_stack **a, t_stack **b, int array_size, int *count)
{
	int	pivot1;
	int	pivot2;
	int	turn;

	pivot1 = pivot_answer(b, array_size);
	pivot2 = pivot_answer2(b, array_size);
	turn = -1;
	while (++turn < array_size)
	{
		if ((*b)->top->content < pivot2)
			sort_alogorithm_rb_b(b, &count[2]);
		else
		{
			sort_alogorithm_pa_b(a, b, &count[1]);
			if ((*a)->top->content < pivot1)
			{
				if ((*b)->top != NULL && ((*b)->top->content < pivot2)
					&& turn + 1 < array_size)
					sort_alo_rr_b(a, b, &count[2], &turn);
				else
					ra(a);
				count[0]++;
			}
		}
	}
}

void	b_to_a(t_stack **a, t_stack **b, int array_size)
{
	int	turn;
	int	count[3];

	(*a)->flag = 0;
	if (check_sorted((*b)->top, array_size, B))
		return (push_pa(a, b, array_size));
	if (array_size <= 3)
		return (three_underonly_fuc_b(a, b, array_size));
	reset_count_array(count);
	ra_rb_pb_while_b(a, b, array_size, count);
	a_to_b(a, b, count[1] - count[0]);
	turn = -1;
	while (++turn < count[0])
		rra(a);
	a_to_b(a, b, count[0]);
	turn = -1;
	while (++turn < count[2])
		rrb(b);
	b_to_a(a, b, count[2]);
}
