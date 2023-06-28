/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_underonlyhardcode.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:56:53 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/22 19:03:04 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
		printf("a : %d, b : %d\n" , a ,b);
		if (cnt == 3)
		{
			c = (*stacks)->top->next->next->content;
			printf("c : %d\n" , c);
		}
		if (cnt == 2 || (a < b && b > c && a < c) || (a > b && b < c && a < c)
			|| (a > b && b > c && a > c))
		{
			sa(stacks);
			continue ;
		}
		if ((a > b && b < c))
			ra(stacks);
		else
			rra(stacks);
	}
}

void	under_three_a(t_stack **a_stack, int cnt)
{
	int	a;
	int	b;
	int	c;

	if (cnt == 1 || check_sorted((*a_stack)->top, cnt, A))
		return ;
	while (!(check_sorted((*a_stack)->top, cnt, A)))
	{
		a = (*a_stack)->top->content;
		b = (*a_stack)->top->next->content;
		printf("a : %d, b : %d\n" , a ,b);
		if (cnt == 3)
		{
			c = (*a_stack)->top->next->next->content;
			printf("c : %d\n" , c);
		}
		if (cnt == 2 || (a > b && a > c) || (c > a && c > b))
			sa(a_stack);
		else if ((b > a && b > c))
		{
			ra(a_stack);
			sa(a_stack);
			rra(a_stack);
		}
	}
}

void	three_only_b(t_stack **stacks, int cnt)
{
	int	a;
	int	b;
	int	c;

	if (cnt == 1 || check_sorted((*stacks)->top, cnt, B))
		return ;
	while (!(check_sorted((*stacks)->top, cnt, B)))
	{
		a = (*stacks)->top->content;
		b = (*stacks)->top->next->content;
		printf("a : %d, b : %d\n" , a ,b);
		if (cnt == 3)
		{
			c = (*stacks)->top->next->next->content;
			printf("c : %d\n" , c);
		}
		if (cnt == 2 || (a > b && b < c && a > c) || (a < b && b > c && a > c)
			|| (a < b && b < c && a < c))
		{
			sb(stacks);
			continue ;
		}
		if (a < b && b > c)
			rb(stacks);
		else
			rrb(stacks);
	}
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
		printf("a : %d, b : %d\n" , a ,b);
		if (cnt == 3)
		{
			c = (*b_stack)->top->next->next->content;
			printf("c : %d\n" , c);
		}
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
	}
}
