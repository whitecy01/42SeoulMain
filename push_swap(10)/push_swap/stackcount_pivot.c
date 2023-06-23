/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stackcount_pivot.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 03:52:49 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/23 14:28:36 by jaeyojun         ###   ########seoul.kr  */
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
	int		result;

	j = 0;
	tmp = (*stack)->top;
	while (j < count && tmp->next)
	{
		j++;
		tmp = tmp->next;
	}
	array = ch_array_quick_sort(stack, count);
	result = array[count - (count / 3) - 1];
	free(array);
	return (result);
}

int	pivot_answer2(t_stack **stack, int array_size)
{
	int		*array;
	t_node	*tmp;
	int		j;
	int		result;

	j = 0;
	tmp = (*stack)->top;
	while (j < array_size && tmp->next)
	{
		j++;
		tmp = tmp->next;
	}
	array = ch_array_quick_sort(stack, array_size);
	result = array[array_size / 3];
	free(array);
	return (result);
}
