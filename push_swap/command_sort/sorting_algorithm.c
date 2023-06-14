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

//알고리즘

int	pivot_answer(t_stack **stack, int count)
{
	int *array;

	t_node *tmp;
	int j = 0;
	tmp = (*stack)->top;
	while (j < count)
	{
		printf("struct[%d] : %d\n", j , tmp->content);
		j++;
		tmp =tmp->next;
	}
	array = ch_array_quick_sort(stack, count);
	
	for (int i =0; i<count; i++)
		printf("array[%d] : %d\n", i, array[i]);

    if (count % 2 == 0) {
			printf("debug\n");
        return (array[count / 2 - 1] + array[count / 2]) / 2;
    } else {
		printf("debug\n");
        return array[count / 2];
    }
}

int	pivot_answer2(t_stack **stack, int pivot1)
{
	int *array;
	t_node *tmp;
	int count;
	t_node	*loc;
	int i;
	
	count = 0;
	tmp = (*stack)->bottom;
	while (1)
	{
		if (tmp->content == pivot1)
			break;
		count++;
	}
	loc = (*stack)->bottom;
	array = (int *)malloc(sizeof(int) * count);
	i = 0;
	while (i < count)
	{
		array[i] = loc->content;
		i++;
		loc = loc->next;
	}
	quick_sort(array, 0, count - 1);
    if (count % 2 == 0) {
        return (array[count / 2 - 1] + array[count / 2]) / 2;
    } else {
        return array[count / 2];
    }
}



void	a_to_b(t_stack **a, t_stack **b, int array_size)
{
	int pivot1;
	//int pivot2;

	// if (array_size == 3)
	// 	return ;
	pivot1 = pivot_answer(a, array_size);
	//pivot2 = pivot_answer2(a, array_size - pivot1);
	printf("pivot 1 : %d \n", pivot1);
	//printf("pivot 2 : %d \n", pivot2);
	printf("b->size : %d \n", (*b)->size);
}

//

void	sort_algorithm(t_stack **a, t_stack **b, int array_size)
{
	//int	*array;

	printf("%d\n", (*b)->size);
	//array = ch_array_quick_sort(a, array_size);


	a_to_b(a, b, array_size);

}
