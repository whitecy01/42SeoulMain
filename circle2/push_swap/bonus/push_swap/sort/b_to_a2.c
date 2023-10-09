/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_to_a2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:50:39 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/18 20:02:33 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../head/push_swap.h"

void	push_pa(t_stack **a, t_stack **b, int array_size)
{
	while (array_size-- > 0)
		pa(a, b);
}

void	sort_alogorithm_rb_b(t_stack **b, int *rb_count)
{
	rb(b);
	(*rb_count)++;
}

void	sort_alogorithm_pa_b(t_stack **a, t_stack **b, int *pa_count)
{
	pa(a, b);
	(*pa_count)++;
}

void	sort_alo_rr_b(t_stack **a, t_stack **b, int *rb_count, int *turn)
{
	rr(a, b);
	(*rb_count)++;
	(*turn)++;
}
