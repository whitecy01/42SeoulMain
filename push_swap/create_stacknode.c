/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_stacknode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:25:19 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/03 14:03:04 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

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

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	if (new == NULL)
		return ;
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}


void	stack_a_create_node(int *array, int array_size, t_stack **stack)
{
	t_node	*append_new_node;
	int		i;

	i = 0;
	while (i < array_size)
	{
		append_new_node = create_node(array[i]);
		if ((*stack->top) == NULL)
			(*stack)->top = append_new_node;
		else
		{
			ft_lstaddback(&((*stack)->top), append_new_node);
		}	
	}
}

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
