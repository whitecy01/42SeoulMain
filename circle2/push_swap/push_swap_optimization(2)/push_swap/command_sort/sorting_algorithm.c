/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_algorithm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:38:25 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/17 18:48:21 by jaeyojun         ###   ########seoul.kr  */
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
		////printf("loc->co : %d\n", loc->content);
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
	
	//p1 구하기 max
	//int max = array[count - 1];
	//int min = array[0];

	//p1 = max - cnt / 3;
	//p2 = cnt / 3 + min;
	//int p1 = max - count / 3;
	

	return (array[count - (count / 3) - 1]);
	//return (array[p1 - 1]);
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

	//p2
	//int max = array[count - 1];
	//int min = array[0];

	//p1 = max - cnt / 3;
	//p2 = cnt / 3 + min;
	//int p2 = array_size / 3 + min;
	////printf("min: %d a_s: %d p2: %d\n", min, array_size, p2);
	//exit(1);

	//return (array[count - (count / 3) - 1]);
	//return (array[p2 - 1]);
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

void	three_only_a(t_stack **stacks, int cnt)
{
	int	a;
	int	b;
	int	c;

	if (check_sorted((*stacks)->top, cnt, A))
		return ;
	while (!(check_sorted((*stacks)->top, cnt, A)))
	{
		a = (*stacks)->top->content;
		b = (*stacks)->top->next->content;
		if (cnt == 3)
			c = (*stacks)->top->next->next->content;
		if (cnt == 2 || (a > b && a > c) || (c > a && c > b))
		{
			sa(stacks);
			continue ;
		}
		if ((b > a && b > c))
			rra(stacks);
		else
			ra(stacks);
	}
}

void	under_three_a(t_stack **a_stack, int cnt)
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

void	three_only_b(t_stack **stacks, int cnt)
{
	int	a;
	int	b;
	int	c;

	if (check_sorted((*stacks)->top, cnt, B))
		return ;
	while (!(check_sorted((*stacks)->top, cnt, B)))
	{
		a = (*stacks)->top->content;
		b = (*stacks)->top->next->content;
		if (cnt == 3)
			c = (*stacks)->top->next->next->content;
		if (cnt == 2 || (a < b && a < c) || (c < a && c < b))
		{
			sb(stacks);
			continue ;
		}
		if (b < a && b < c)
			rrb(stacks);
		else
			rb(stacks);
	}
	// while (cnt--)
	// 	pa(stacks);
}


void	under_three_b(t_stack **b_stack, int cnt)
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

// void	b_to_a(t_stack **a, t_stack **b, int array_size)
// {
// 	int	pivot1;
// 	int	pivot2;
// 	int	turn;
// 	int	rb_count = 0;
// 	int	ra_count = 0;
// 	int	pa_count = 0;

// 	if (array_size <= 3)
// 	{
// 		under_cnt_three_b(b, array_size);
// 		//check_list(a, b);
// 		while (array_size--)
// 			pa(a, b);
// 		return ;
// 	}
// 	pivot1 = pivot_answer(b, array_size);
// 	pivot2 = pivot_answer2(b, array_size);
// 	while (array_size--)
// 	{
// 		if ((*b)->top->content <= pivot2)
// 		{
// 			rb(b);
// 			rb_count++;
// 		}
// 		else
// 		{
// 			pa(a, b);
// 			pa_count++;
// 			if ((*a)->top->content <= pivot1)
// 			{
// 				ra(a);
// 				ra_count++;
// 			}
// 		}
// 		//check_list(a, b);
// 	}
	
// 	a_to_b(a, b, pa_count - ra_count);

// 	turn = -1;
// 	while (++turn < ra_count)
// 		rra(a);

// 	a_to_b(a, b, ra_count);

// 	turn = -1;
// 	while (++turn < rb_count)
// 		rrb(b);

// 	b_to_a(a, b, rb_count);
// }

// void	a_to_b(t_stack **a, t_stack **b, int array_size)
// {
// 	int	pivot1;
// 	int	pivot2;
// 	int	turn;
// 	int	ra_count = 0;
// 	int	rb_count = 0;
// 	int	pb_count = 0;

// 	if (array_size <= 3)
// 	{
// 		under_cnt_three_a(a, array_size);
// 		//check_list(a, b);
// 		return ;
// 	}
// 	pivot1 = pivot_answer(a, array_size);	
// 	pivot2 = pivot_answer2(a, array_size);
// 	while (array_size)
// 	{
// 		if ((*a)->top->content >= pivot1)
// 		{
// 			ra(a);
// 			ra_count++;
// 		}
// 		else
// 		{
// 			pb(a, b);
// 			pb_count++;
// 			if ((*b)->top->content >= pivot2)
// 			{
// 				rb(b);
// 				rb_count++;
// 			}
// 		}
// 		//check_list(a, b);
// 		array_size--;
// 	}
// 	//첫번째 재귀일 때  rra를 할 필요가 없음.

// //	while (turn < rb_count && turn < ra_count && (count == 0))
// 	turn = 0;
// 	while (turn < rb_count && turn < ra_count)
// 	{
// 		rrr(a, b);
// 		turn++;
// 	}
// 	while (turn < rb_count || turn < ra_count)
// 	{
// 		if (turn < rb_count)
// 			rrb(b);
// 		if (turn < ra_count)
// 			rra(a);
// 		turn++;
// 	}

// 	// turn = -1;
// 	// while (++turn < rb_count)
// 	// 	rrb(b);
// 	// turn = -1;
// 	// while (++turn < ra_count)
// 	// 	rra(a);
// 	//check_list(a, b);
// 	a_to_b(a, b, ra_count);
// 	b_to_a(a, b, rb_count);
// 	b_to_a(a, b, pb_count - rb_count);
// }

// void	sort_algorithm(t_stack **a, t_stack **b, int array_size)
// {
// 	//int count = 1;
// 	a_to_b(a, b, array_size);
// }



//----------------------------------밑에 총길이 추가


void	b_to_a(t_stack **a, t_stack **b, int array_size)
{
		//write(1, "fuck\n", 5);
	//printf("come_in_b_to_a\n");
	(*a)->flag = 0;
	int	pivot1;
	int	pivot2;
	int	turn;
	int	rb_count = 0;
	int	ra_count = 0;
	int	pa_count = 0;
	int stack_b_count;

	stack_b_count = stack_top_count(b);
	if (array_size <= 3)
	{
		//////printf("check!!!!!\n");
		if (stack_b_count == array_size)
		{
			three_only_b(b, array_size);
			while (array_size-- > 0)
				pa(a, b);
			//check_list(a, b);
		}
		else
		{
			under_three_b(b, array_size);
		//check_list(a, b);
			while (array_size-- > 0)
				pa(a, b);
		}
		check_list(a, b);
		////printf("check!!!!!\n");
		return ;
	}
	pivot1 = pivot_answer(b, array_size);
	pivot2 = pivot_answer2(b, array_size);
	//printf("pivot1 : %d, pivot2: %d , array_size : %d\n", pivot1, pivot2, array_size);
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
		check_list(a, b);
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


int	stack_top_count(t_stack **stack)
{
	t_node *tmp;
	int count = 0;

	tmp = (*stack)->top;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);

}

void	a_to_b(t_stack **a, t_stack **b, int array_size)
{
	//write(1, "fuck \n", 5);
	//printf("come_in_a_to_b\n");
	int	pivot1;
	int	pivot2;
	int	turn;
	int	ra_count = 0;
	int	rb_count = 0;
	int	pb_count = 0;
	int stack_a_count;
	
	stack_a_count = stack_top_count(a);
	////printf("stack_acount : %d, array_size : %d\n", stack_a_count, array_size);
	
	if (array_size <= 3)
	{
		if (array_size == stack_a_count)
		{
			//check_list(a, b);
			three_only_a(a, array_size);
		}
		else
			under_three_a(a, array_size);
		check_list(a, b);
		return ;
	}
	pivot1 = pivot_answer(a, array_size);	
	pivot2 = pivot_answer2(a, array_size);
	//printf("pivot1 : %d, pivot2: %d , array_size : %d\n", pivot1, pivot2, array_size);
	turn = 0;
	while (turn < array_size)
	{
		if ((*a)->top->content >= pivot1)
		{
			ra(a);
			ra_count++;
		}
		else
		{
			// if ((*a)->flag == 1)
			// {
			// 	pb(a, b);
			// 	rb_count++;
			// 	if ((*b)->top->content < pivot2)
			// 	{
			// 		rb(b);
			// 		pb_count++;
			// 	}
			// }
			//else
			//{
				pb(a, b);
				pb_count++;
				if ((*b)->top->content >= pivot2)
				{
					rb(b);
					rb_count++;
				}
			//}
		}
		//check_list(a, b);
		//array_size--;
		turn++;
	}
	//첫번째 재귀일 때  rra를 할 필요가 없음.


//	while (turn < rb_count && turn < ra_count && (count == 0))
	
	turn = 0;
	if ((stack_a_count != array_size))
	{
		while (turn < rb_count && turn < ra_count)
		{
			rrr(a, b);
			turn++;
		}
	}
	while ((turn < rb_count || turn < ra_count))
	{
		if (turn < rb_count)
			rrb(b);
		if (stack_a_count != array_size)
		{
			if (turn < ra_count)
				rra(a);
		}
		turn++;
	}

	// turn = 0;
	// if ((stack_a_count != array_size))
	// {
	// 	while (turn < rb_count && turn < ra_count)
	// 	{
	// 		rrr(a, b);
	// 		turn++;
	// 	}
	// }
	// while ((turn < rb_count || turn < ra_count))
	// {
	// 	if (turn < rb_count)
	// 		rrb(b);
	// 	if (stack_a_count != array_size)
	// 	{
	// 		if (turn < ra_count)
	// 			rra(a);
	// 	}
	// 	turn++;
	// }


	// turn = -1;
	// while (++turn < rb_count)
	// 	rrb(b);
	// turn = -1;
	// while (++turn < ra_count)
	// 	rra(a);
	////printf("--------------\n");
	check_list(a, b);
	// if ((*a)->flag == 1)
	// {
	// 	a_to_b(a, b, ra_count);
	// 	//b_to_a(a, b, rb_count);
	// 	//b_to_a(a, b, pb_count - rb_count);
	// }
	//printf("rb_%d   pb_%d\n", rb_count, pb_count);
	//exit(1);
	a_to_b(a, b, ra_count);

	//if ((*a)->flag != 1)
	b_to_a(a, b, rb_count);
	//else
	//	b_to_a(a, b, rb_count - pb_count);

	//if ((*a)->flag != 1)
		b_to_a(a, b, pb_count - rb_count);
	//else 
	//	b_to_a(a, b, rb_count - pb_count);
}

// int		a_to_b_start(t_stack **a, t_stack **b, int array_size)
// {
// 	int	pivot1;
// 	int	pivot2;
// 	int	turn;
// 	int	count[3];
// 	int	ra_count = 0;
// 	int	rb_count = 0;
// 	int	pb_count = 0;
// 	int stack_a_count;
	
// 	stack_a_count = stack_top_count(a);
// 	//////printf("stack_acount : %d, array_size : %d\n", stack_a_count, array_size);

// 	if (array_size <= 3)
// 	{
// 		if (array_size == stack_a_count)
// 		{
// 			//check_list(a, b);
// 			three_only_a(a, array_size);
// 		}
// 		else
// 			under_three_a(a, array_size);
// 		//check_list(a, b);
// 		//return ;
// 	}
// 	pivot1 = pivot_answer(a, array_size);	
// 	pivot2 = pivot_answer2(a, array_size);
	
// 	turn = 0;
// 	while (turn < array_size)
// 	{
// 		if ((*a)->top->content >= pivot1)
// 		{
// 			ra(a);
// 			count[0]++;
// 		}
// 		else
// 		{
// 			pb(a, b);
// 			pb_count++;
// 			if ((*b)->top->content <= pivot2)
// 			{
// 				rb(b);
// 				rb_count++;
// 			}
// 		}
// 		//check_list(a, b);
// 		//array_size--;
// 		turn++;
// 	}
// 	return (count);

// }

void	sort_algorithm(t_stack **a, t_stack **b, int array_size)
{
	//int *count;
	//count = a_to_b_start(a, b, array_size);
	//a_to_b(a, b, ra_count);
	//먼저 정렬하고
	//3분할하고
	a_to_b(a, b, array_size);
	//a_to_b(a, b, count[0]);
	//b_to_a(a, b, count[1]);
	//b_to_a(a, b, count[2] - count[1]);
	check_list(a,b);
}
