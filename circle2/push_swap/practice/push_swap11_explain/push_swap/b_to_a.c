/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_to_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 06:55:11 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/25 15:09:09 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra_rb_pb_while_b(t_stack **a, t_stack **b, int array_size, int *count)
{
	int	pivot1;
	int	pivot2;
	int	turn; // count[0] == ra_count count[1] == pa_count, count[2] == rb_count;

	pivot1 = pivot_answer(b, array_size);
	pivot2 = pivot_answer2(b, array_size);
	printf("pivot1 : %d,  pivot2 : %d\n", pivot1, pivot2);
	printf("arry_size : %d\n", array_size);
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
		check_list(a,b);
	}
}

void	b_to_a(t_stack **a, t_stack **b, int array_size)
{
	printf("b_to_a array_size : %d\n", array_size);
	int	turn;
	int count[3]; // count[0] == ra_count count[1] == pa_count, count[2] == rb_count;

	(*a)->flag = 0;
	if (check_sorted((*b)->top, array_size, B))
	{
		check_list(a,b);
		push_pa(a, b, array_size);

		check_list(a,b);
		return ;
	}
	if (array_size <= 3)
	{
		check_list(a,b);
		three_underonly_fuc_b(a, b, array_size);
		check_list(a,b);
		return ;
	}
	reset_count_array(count);
	ra_rb_pb_while_b(a, b, array_size, count);

	check_list(a,b);
		printf("ra_count == count[0] : %d\n", count[0]);
	printf("pb_count == count[1] : %d\n", count[1]);
	printf("rb_count == count[2] : %d\n", count[2]);

	printf("b_to_a -> come_a_to_b_ pa_count - ra_count : %d\n", count[1] - count[0]); //큰놈들
	a_to_b(a, b, count[1] - count[0]);
	turn = -1;
	while (++turn < count[0])
		rra(a);
	printf("b_to_a -> come_a_to_b_ra_count : %d\n", count[0]); // 중간놈들 
	a_to_b(a, b, count[0]);
	turn = -1;
	while (++turn < count[2])
		rrb(b);
	printf("b_to_a -> come_b_to_a_rb_count : %d\n", count[2] );
	b_to_a(a, b, count[2]);
}
