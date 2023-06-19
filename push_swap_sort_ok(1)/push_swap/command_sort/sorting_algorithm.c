/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_algorithm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:38:25 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/16 16:52:56 by jaeyojun         ###   ########seoul.kr  */
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

int	*ch_array_quick_sort(t_stack **stack, int array_size)
{
	int		*array;
	int		i;
	t_node	*loc;

	loc = (*stack)->top;
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
	return (array[array_size / 3 - 1]);
}

int	check_sorted(t_node *tmp, int cnt, int stack)
{
	int	i;

	if (cnt == 1)
		return (1);
	i = 1;
	if (stack == A)
	{
		while (i < cnt && tmp->next)
		{
			if (tmp->content > tmp->next->content)
				return (0);
			tmp = tmp->next;
			i++;
		}
	}
	else if (stack == B)
	{
		while (i < cnt && tmp->next)
		{
			if (tmp->content < tmp->next->content)
				return (0);
			tmp = tmp->next;
			i++;
		}
	}
	return (1);
}

void	under_cnt_three_a(t_stack **a_stack, int cnt)
{
	int	a;
	int	b;
	int	c;

	if (check_sorted((*a_stack)->top, cnt, A))
		return ;
	while (!(check_sorted((*a_stack)->top, cnt, A)))
	{
		a = (*a_stack)->top->content;
		b = (*a_stack)->top->next->content;
		if (cnt == 3)
			c = (*a_stack)->top->next->next->content;
		if (cnt == 2 || (a > b && a > c) || (c > a && c > b))
			sa(a_stack);
		else if ((b > a && b > c))
		{
			ra(a_stack);
			sa(a_stack);
			rra(a_stack);
		}
		//check_list(a_stack, b_);
	}
}

void	under_cnt_three_b(t_stack **b_stack, int cnt)
{
	int	a;
	int	b;
	int	c;

	if (check_sorted((*b_stack)->top, cnt, B))
		return ;
	while (!(check_sorted((*b_stack)->top, cnt, B)))
	{
		a = (*b_stack)->top->content;
		b = (*b_stack)->top->next->content;
		if (cnt == 3)
			c = (*b_stack)->top->next->next->content;
		if (cnt == 2 || (a < b && a < c) || (c < a && c < b))
		{
			sb(b_stack);
		}
		else if ((b < a && b < c))
		{
			rb(b_stack);
			sb(b_stack);
			rrb(b_stack);
		}
		//check_list(a_stack, b_stack);
	}
}

void	b_to_a(t_stack **a, t_stack **b, int array_size)
{
	int	pivot1;
	int	pivot2;
	int	turn;
	int	rb_count = 0;
	int	ra_count = 0;
	int	pa_count = 0;

	if (array_size <= 3)
	{
		under_cnt_three_b(b, array_size);
		//check_list(a, b);
		while (array_size--)
			pa(a, b);
		return ;
	}
	pivot1 = pivot_answer(b, array_size);
	pivot2 = pivot_answer2(b, array_size);
	while (array_size--)
	{
		if ((*b)->top->content <= pivot2)
		{
			rb(b);
			rb_count++;
		}
		else
		{
			pa(a, b);
			pa_count++;
			if ((*a)->top->content <= pivot1)
			{
				ra(a);
				ra_count++;
			}
		}
		//check_list(a, b);
	}
	a_to_b(a, b, pa_count - ra_count);
	turn = -1;
	while (++turn < ra_count)
		rra(a);
	a_to_b(a, b, ra_count);
	turn = -1;
	while (++turn < rb_count)
		rrb(b);
	b_to_a(a, b, rb_count);
}

void	a_to_b(t_stack **a, t_stack **b, int array_size)
{
	int	pivot1;
	int	pivot2;
	int	turn;
	int	ra_count = 0;
	int	rb_count = 0;
	int	pb_count = 0;

	if (array_size <= 3)
	{
		under_cnt_three_a(a, array_size);
		//check_list(a, b);
		return ;
	}
	pivot1 = pivot_answer(a, array_size);	
	pivot2 = pivot_answer2(a, array_size);
	while (array_size)
	{
		if ((*a)->top->content >= pivot1)
		{
			ra(a);
			ra_count++;
		}
		else
		{
			pb(a, b);
			pb_count++;
			if ((*b)->top->content >= pivot2)
			{
				rb(b);
				rb_count++;
			}
		}
		//check_list(a, b);
		array_size--;
	}
	turn = -1;
	while (++turn < rb_count)
		rrb(b);
	turn = -1;
	while (++turn < ra_count)
		rra(a);
	//check_list(a, b);
	a_to_b(a, b, ra_count);
	b_to_a(a, b, rb_count);
	b_to_a(a, b, pb_count - rb_count);
}

void	sort_algorithm(t_stack **a, t_stack **b, int array_size)
{
	a_to_b(a, b, array_size);
}
