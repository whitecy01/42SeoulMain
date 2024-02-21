/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_to_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 06:54:49 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/18 08:27:53 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../head/push_swap.h"

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

void	a_to_b(t_stack **a, t_stack **b, int array_size)
{
	int	pivot1;
	int	pivot2;
	int	turn;
	int	ra_count;
	int	rb_count;
	int	pb_count;
	int stack_a_count;

	if (check_sorted((*a)->top, array_size, A))
		return ;
	ra_rb_pb_reset(&ra_count, &rb_count, &pb_count);
	stack_a_count = stack_top_count(a);
	if (array_size <= 3)
		return (three_underonly_fuc_a(a, array_size));
	pivot1 = pivot_answer(a, array_size);
	pivot2 = pivot_answer2(a, array_size);
	turn = 0;
	while (turn < array_size)
	{
		if ((*a)->top->content >= pivot1)
			sort_alogorithm_ra(a, &ra_count);
		else
		{
			sort_alogorithm_pb(a, b, &pb_count);
			if ((*b)->top->content > pivot2)
			{
				if ((*a)->top != NULL && ((*a)->top->content >= pivot1)
					&& turn + 1 < array_size)
					one_plus_one_rr(a, b, &ra_count, &turn);
				else
					rb(b);
				rb_count++;
			}
		}
		turn++;
	}
	turn = 0;
	if ((stack_a_count != array_size))
		turn = ra_rb_sum_rrr(ra_count, rb_count, a, b);
	//rrb
	rrb_a_to_b(rb_count, b, turn);
	//rra
	//rra_a_to_b(ra_count, a, turn, array_size);
	while (turn < ra_count)
	{
		if (stack_a_count != array_size)
		{
			if (turn < ra_count)
				rra(a);
		}
		turn++;
	}
	a_to_b(a, b, ra_count);
	b_to_a(a, b, rb_count);
	b_to_a(a, b, pb_count - rb_count);
}
