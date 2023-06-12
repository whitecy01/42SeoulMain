/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_algorithm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:38:25 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/12 02:20:09 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../head/push_swap.h"

void	swap(int *first, int *second)
{
	int	tmp;

	tmp = *second;
	*second = *first;
	*first = tmp;
}

int	partiton(int *array, int start, int end)
{
	int	pivot;
	int	i;
	int	j;

	pivot = array[end];
	i = (start - 1);
	j = start;
	while (j <= end - 1)
	{
		if (array[j] <= pivot)
		{
			i++;
			swap(&array[i], &array[j]);
		}
		j++;
	}
	swap(&array[i + 1], &array[end]);
	return (i + 1);
}

void	quick_sort(int *array, int start, int end)
{
	int	p;

	if (start < end)
	{
		p = partiton(array, start, end);
		quick_sort(array, start, p - 1);
		quick_sort(array, p + 1, end);
	}
}

int	*ch_array_quick_sort(t_stack **a, int array_size)
{
	int		*array;
	int		i;
	t_node	*loc;

	loc = (*a)->top;
	array = (int *)malloc(sizeof(int) * array_size);
	i = 0;
	while (i < array_size)
	{
		array[i] = loc->content;
		i++;
		loc = loc->next;
	}
	quick_sort(array, 0, array_size - 1);
	return (array);
}

void	stack_sort_algroithm(t_stack **a, t_stack **b, int array_size, int *array)
{
	int	pivot1;
	int	pivot2;
	int	i;

	i = 0;
	while (i < array_size)
	{
		pivot1 = array_size / 3;
		pivot2 = (array_size / 3) - pivot1;
	}
}

void	sort_algorithm(t_stack **a, t_stack **b, int array_size)
{
	int	*array;

	printf("%d\n", (*b)->size);
	array = ch_array_quick_sort(a, array_size);
	stack_sort_algroithm(a, b, array_size, array);

}
