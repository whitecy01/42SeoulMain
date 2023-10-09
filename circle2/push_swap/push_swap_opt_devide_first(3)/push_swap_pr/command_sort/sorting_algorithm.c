/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_algorithm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:38:25 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/16 18:24:31 by jaeyojun         ###   ########seoul.kr  */
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
	//printf("array_size : %d\n", array_size);
	//printf("loc_content : %d\n", loc->content);
	//printf("loc_content : %d\n", loc->next->content);
	//printf("loc_content : %d\n", loc->next->next->content);
	//printf("loc_content : %d\n", loc->next->next->next->content);
	
	while (i < array_size)
	{
		
		array[i] = loc->content;
		//printf("loc->co : %d\n", loc->content);
		i++;
		loc = loc->next;

	}
	
	//write(1, "fucking2\n", 9);
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
		printf("struct[%d] : %d\n", j , tmp->content);
		j++;
		tmp = tmp->next;
	}
	//printf("count : %d\n", count);
	array = ch_array_quick_sort(stack, count);

	// for (int i =0; i<count; i++)
	// 	printf("array[%d] : %d\n", i, array[i]);
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
		//printf("struct[%d] : %d\n", j , tmp->content);
		j++;
		tmp = tmp->next;
	}
	array = ch_array_quick_sort(stack, array_size);
	// for (int i =0; i<array_size; i++)
	// 	printf("array[%d] : %d\n", i, array[i]);
	return (array[array_size / 3 - 1]);
}

int	check_sorted(t_node *tmp, int cnt, int stack)
{
	int i;

	//printf("tmp - > content : %d\n", tmp->content);
	if (cnt == 1)
		return (1);
	i = 1;
	if (stack == A)
	{
		while (i < cnt  && tmp->next)
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
			//printf("tmp->content : %d\n", tmp->content);
			if (tmp->content < tmp->next->content)
				return (0);
			tmp = tmp->next;
			i++;
		}
	}
	return (1);
}



void    under_cnt_three_a(t_stack **a_stack, t_stack **b_, int cnt)
{
    int        a;
    int        b;
    int        c;

	//printf("b->size : %d\n", (*b_)->size);
    if (check_sorted((*a_stack)->top, cnt, A))
        return ;
    while (!(check_sorted((*a_stack)->top, cnt, A)))
    {
		write(1, "ilko_code\n" , 10);
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
		check_list(a_stack, b_);
    }
}


void    under_cnt_three_b(t_stack **a_stack, t_stack **b_stack, int cnt)
{
	//write(1, "1\n" , 2);
	//printf("debug");
    int        a;
    int        b;
    int        c;

    if (check_sorted((*b_stack)->top, cnt, B))
        return ;
	// printf("sorted : %d\n" ,check_sorted((*b_stack)->top, cnt, B) );
	// 	return;
    while (!(check_sorted((*b_stack)->top, cnt , B)))
    { 
		//if (check_sorted((*b_stack)->top, cnt, B) == 1)
			//write(1, "1\n", 1);
		//else if(check_sorted((*b_stack)->top, cnt, B) == 0)
			//write(1, "0\n", 1);
		//printf("sorted : %d\n" ,check_sorted((*b_stack)->top, cnt, B) );
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
		check_list(a_stack, b_stack);
    }
}


void	b_to_a(t_stack **a, t_stack **b, int array_size)
{
	printf("come in b_to_a\n");
	int	pivot1;
	int	pivot2;
	int	turn;
	int	rb_count = 0;
	int	ra_count = 0;
	int	pa_count = 0;
	//write(1, "fucking : 1\n" , 12);

	printf("b_to_a : array_size : %d\n" ,array_size);
	if (array_size <= 3)
	{
		//3개 이하 일 때 정렬
		under_cnt_three_b(a, b, array_size);
		check_list(a, b);
		while (array_size--)
			pa(a, b);
		
		return ;
	}
	
	pivot1 = pivot_answer(b, array_size);
	//write(1, "fucking2\n", 9);
	pivot2 = pivot_answer2(b, array_size);

	//printf("pivod1 : %d, pivot2 : %d\n", pivot1, pivot2);
	printf("p1 : %d p2 : %d arrayy_size : %d\n", pivot1, pivot2, array_size);
	// printf("top : %d", (*b)->size);
	//exit(1);
	
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
		//printf("array size : %d\n" , array_size);
		check_list(a, b);
	}
	//-----------------------------일성--------------------
	// while (array_size--)
	// {
	// 	if ((*b)->top->content <= pivot2)
	// 	{
	// 		rb(b);
	// 		rb_count++;
	// 	}
	// 	else
	// 	{
	// 		pa(a, b);
	// 		pa_count++;
	// 		if ((*a)->top->content <= pivot1)
	// 		{
	// 			ra(b);
	// 			ra_count++;
	// 		}
	// 	}
	// }
	//printf("ra_count : %d pa_count : %d, ra_count : %d\n", ra_count, pa_count, ra_count);
		//-----------------------------일성--------------------
	
	//큰놈 정렬
	a_to_b(a, b, pa_count - ra_count);
	
	turn = -1;
	while (++turn < ra_count)
	{
		printf("turn : %d\n", turn);
		rra(a);
	}
	//중간놈 정렬 
	a_to_b(a, b, ra_count);
	turn = -1;
	while (++turn < rb_count)
	{
		printf("turn : %d\n", turn);
		rrb(b);
	}
	//printf("rb_cou : %d pb_cou : %d\n", rb_count, pa_count);
	//작은놈 정렬 
	b_to_a(a, b, rb_count);
	

	//-----------------------------일성--------------------
	// a_to_b(a, b, ra_count);
	// // turn = -1;
	// // while (++turn < ra_count)
	// // {
	// // 	printf("turn : %d\n", turn);
	// // 	rra(a);
	// // }
	// a_to_b(a, b, pa_count);
	// while (++turn < rb_count)
	// {
	// 	printf("turn : %d\n", turn);
	// 	rrb(b);
	// }
	// //printf("rb_cou : %d pb_cou : %d\n", rb_count, pa_count);
	// b_to_a(a, b, rb_count);
	//------------------------일성---------------------
}


void	a_to_b(t_stack **a, t_stack **b, int array_size)
{
	printf("come in a_to_b\n");
	int	pivot1;
	int	pivot2;
	int	turn;
	int	ra_count = 0;
	int	rb_count = 0;
	int	pb_count = 0;
	
	//write(1, "here fuck : 1\n" , 14);
	printf("a_to_b_array_size : %d\n", array_size);
	//if (check_sorted(a))
	if (array_size <= 3)
	{
		//3개 이하 일 때 정렬
		//write(1, "retrun : 1\n" , 11);
		//printf("debug");
		under_cnt_three_a(a, b, array_size);
		//ㅊㅔ크리스트 넣기 
		write(1, "check!!!!\n", 10);
		check_list(a, b);
		return ;
	}
	pivot1 = pivot_answer(a, array_size);
		
	pivot2 = pivot_answer2(a, array_size);
	printf("p1 : %d p2 : %d arrayy_size : %d\n", pivot1, pivot2, array_size);
	//printf("pivod1 : %d, pivot2 : %d\n", pivot1, pivot2);
	// printf("top : %d", (*b)->size);
	//exit(1);
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
				//rb_count = 4인데 4번 중에 1번은 값이 하나라서 rb가 실행되지 않음.
				rb_count++;
			}
		}
		printf("array size : %d\n" , array_size);
		check_list(a, b);
		array_size--;
	}
	printf("ra_count : %d pb_count : %d, rb_count : %d\n", ra_count, pb_count, rb_count);
	
	
	
	turn = 0;
	while (turn < rb_count && turn < ra_count)
	{
		rrr(a, b);
		turn++;
	}
	while (turn < rb_count || turn < ra_count)
	{
		if (turn < rb_count)
			rrb(b);
		if (turn < ra_count)
			rra(a);
		turn++;
	}

	// turn = -1;
	// while (++turn < rb_count)
	// 	rrb(b);
		

	//---------------------일성----------------

	//이 부분필요없음	
	// turn = -1;
	// while (++turn < ra_count)
	// 	rra(a);
	// turn = -1;
	// while (++turn < rb_count)
	// 	rrb(b);
	//printf("ra_count : %d pb_count : %d, rb_count : %d\n", ra_count, pb_count, rb_count);
	//---------------------일성----------------

	check_list(a, b);
	a_to_b(a, b, ra_count);
	//write(1, "here : 1\n" , 9);
	//printf("debug");
	b_to_a(a, b, rb_count);
	b_to_a(a, b, pb_count - rb_count);
}

void	sort_algorithm(t_stack **a, t_stack **b, int array_size)
{
	// rra(a);
	// rra(a);
	// rra(a);

	// printf("b->size : %d\n" , (*b)->size);
	// printf("array_size : %d\n" , array_size);
	// while((*a)->top)
	// {
	// 	printf("a->top : %d\n" , (*a)->top->content);
	// 	(*a)->top = (*a)->top->next;
	// }
	a_to_b(a, b, array_size);
}
