/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_to_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 06:54:49 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/23 19:47:05 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra_rb_pb_while(t_stack **a, t_stack **b, int array_size, int *count)
{
	int	pivot1;
	int	pivot2;
	int	turn;

	pivot1 = pivot_answer(a, array_size);
	pivot2 = pivot_answer2(a, array_size);
	printf("pivot1 : %d,  pivot2 : %d\n", pivot1, pivot2);
	printf("arry_size : %d\n", array_size);
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
		check_list(a,b);
	}
}	

void	a_to_b(t_stack **a, t_stack **b, int array_size)
{
	printf("a_to_b, array_size : %d\n", array_size);
	int	turn;
	int count[3]; // count[0] == ra_count count[1] == pb_count, count[2] == rb_count;
	int stack_a_count;

	if (check_sorted((*a)->top, array_size, A))
	{
				check_list(a,b);
		return ;
	}
	stack_a_count = stack_top_count(a);
	if (array_size <= 3)
	{
				check_list(a,b);
		three_underonly_fuc_a(a, array_size);
				check_list(a,b);
		return ;
	}
	reset_count_array(count);
	ra_rb_pb_while(a, b, array_size, count);
	turn = 0;
	printf("stack_a_count : %d array_size : %d\n", stack_a_count, array_size);
	if ((stack_a_count != array_size))
		turn = ra_rb_sum_rrr(count[0], count[2], a, b);
	rrb_a_to_b(count[2], b, turn);
	while (turn < count[0])
	{
		if (stack_a_count != array_size)
			rra(a);
		turn++;
	}
	check_list(a,b);
	printf("ra_count == count[0] : %d\n", count[0]);
	printf("pb_count == count[1] : %d\n", count[1]);
	printf("rb_count == count[2] : %d\n", count[2]);

	printf("a_to_b -> come_a_to_b_ra_count : %d\n", count[0]);
	a_to_b(a, b, count[0]);

	printf("a_to_b -> come_b_to_a_rb_count : %d\n", count[2]);
	b_to_a(a, b, count[2]);

	printf("a_to_b -> come_b_to_a_pb_count - rb_count : %d\n",  count[1] - count[2]);
	b_to_a(a, b, count[1] - count[2]);
}
