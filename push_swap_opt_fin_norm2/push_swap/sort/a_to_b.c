/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_to_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 06:54:49 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/18 18:45:02 by jaeyojun         ###   ########seoul.kr  */
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

//int형 배열을 만들어서 3개짜리 ra,rb,pb 값을 각각 넣어주고 리턴 
//ra,rb,pb while문을 넘기자, pivot
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
