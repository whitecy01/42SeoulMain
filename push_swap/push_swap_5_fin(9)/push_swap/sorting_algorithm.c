/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_algorithm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:38:25 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/22 19:06:05 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_alogorithm_ra(t_stack **a, int *ra_count)
{
	ra(a);
	(*ra_count)++;
}

void	sort_alogorithm_pb(t_stack **a, t_stack **b, int *pb_count)
{
	pb(a, b);
	(*pb_count)++;
}

void	sort_alogorithm_rb(t_stack **b, int *rb_count)
{
	rb(b);
	(*rb_count)++;
}

void	ra_rb_pb_reset(int *ra_count, int *rb_count, int *pb_count)
{
	*ra_count = 0;
	*rb_count = 0;
	*pb_count = 0;
}

void	sort_algorithm(t_stack **a, t_stack **b, int array_size)
{
	int	pivot1;
	int	pivot2;
	int	ra_count;
	int	rb_count;
	int	pb_count;

	ra_rb_pb_reset(&ra_count, &rb_count, &pb_count);
	if (array_size <= 3)
		three_underonly_fuc_a(a, array_size);
	pivot1 = pivot_answer(a, array_size);
	pivot2 = pivot_answer2(a, array_size);
	while (array_size--)
	{
		if ((*a)->top->content >= pivot1)
			sort_alogorithm_ra(a, &ra_count);
		else
		{
			sort_alogorithm_pb(a, b, &pb_count);
			if ((*b)->top->content < pivot2)
				sort_alogorithm_rb(b, &rb_count);
		}
	}
	a_to_b(a, b, ra_count);
	b_to_a(a, b, pb_count - rb_count);
	b_to_a(a, b, rb_count);
}
