/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_stacknode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:25:19 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/14 23:04:37 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../head/push_swap.h"

t_stack	*create_stack(int array_size, char name)
{
	t_stack	*tmp;

	tmp = (t_stack *)malloc(sizeof(t_stack));
	tmp->size = array_size;
	tmp->name = name;
	tmp->top = NULL;
	tmp->bottom = NULL;
	return (tmp);
}

t_node	*create_node(int array_answer)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (new_node)
	{
		new_node->content = array_answer;
		new_node->prev = NULL;
		new_node->next = NULL;
	}
	return (new_node);
}

void	node_pushback(t_node **pr, t_node *new)
{
	t_node	*tmp;

	if (*pr == NULL)
	{
		*pr = new;
		return ;
	}
	if (!new)
		return ;
	tmp = *pr;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
	new->prev = tmp;
}

void	stack_a_push_node(int *array, int array_size, t_stack **stack)
{
	int		i;
	t_node	*new_node;
	t_node	*pr;

	new_node = create_node(array[0]);
	if (!(((*stack)->top)))
		(*stack)->top = new_node;
	if (array_size == 1)
	{
		(*stack)->bottom = new_node;
		new_node->next = (*stack)->top;
		return ;
	}
	i = 1;
	while (i < array_size)
	{
		pr = create_node(array[i]);
		node_pushback(&new_node, pr);
		i++;
	}
	(*stack)->bottom = pr;
	//pr->next = (*stack)->top;
	//(*stack)->top->prev = pr;
}

//top 위치를 이용해서 넣어주기

// void	stack_a_create_node(int *array, int array_size, t_stack **stack)
// {
// 	t_node	*append_new_node;
// 	int		i;

// 	i = 0;
// 	while (i < array_size)
// 	{
// 		append_new_node = create_node(array[i]);
// 		if (!append_new_node)
// 			return ;
// 		if (!((*stack)->bottom))
// 		{
// 			 (*stack)->bottom = append_new_node;
// 			 (*stack)->top = (*stack)->bottom;
// 		}
// 		else
// 		{
// 			(*stack)->bottom = (*stack)->bottom->next;
// 			(*stack)->bottom = append_new_node;
// 		}
// 		i++;
// 	}
// }
