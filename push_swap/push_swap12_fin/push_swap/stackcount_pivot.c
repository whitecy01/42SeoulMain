/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stackcount_pivot.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 03:52:49 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/26 14:13:41 by jaeyojun         ###   ########seoul.kr  */
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
	int		result;

	array = ch_array_quick_sort(stack, count);
	result = array[count - (count / 3) - 1];
	free(array);
	return (result);
}

int	pivot_answer2(t_stack **stack, int array_size)
{
	int		*array;
	int		result;

	array = ch_array_quick_sort(stack, array_size);
	result = array[array_size / 3];
	free(array);
	return (result);
}
