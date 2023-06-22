/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stackcount_pivot.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 03:52:49 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/22 19:02:57 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	stack_top_count(t_stack **stack)
{
	t_node	*tmp;
	int		count;

	count = 0;
	tmp = (*stack)->top;

	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

int	pivot_answer(t_stack **stack, int count)
{
	int		*array;
	t_node	*tmp;
	int		j;

	j = 0;
	tmp = (*stack)->top;
	while (j < count && tmp->next)
	{
		j++;
		tmp = tmp->next;
	}
	array = ch_array_quick_sort(stack, count);
	return (array[count - (count / 3) - 1]);
}

int	pivot_answer2(t_stack **stack, int array_size)
{
	int		*array;
	t_node	*tmp;
	int		j;

	j = 0;
	tmp = (*stack)->top;
	while (j < array_size && tmp->next)
	{
		j++;
		tmp = tmp->next;
	}
	array = ch_array_quick_sort(stack, array_size);
	return (array[array_size / 3]);
}
