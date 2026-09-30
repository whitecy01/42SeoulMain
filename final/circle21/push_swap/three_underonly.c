/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_underonly.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 04:02:08 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/22 19:03:00 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	three_underonly_fuc_a(t_stack **a, int array_size)
{
	int	stack_a_count;

	stack_a_count = stack_top_count(a);
	if (array_size == stack_a_count)
		three_only_a(a, array_size);
	else
		under_three_a(a, array_size);
	return ;
}

void	three_underonly_fuc_b(t_stack **a, t_stack **b, int array_size)
{
	int	stack_b_count;

	stack_b_count = stack_top_count(b);
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
}
