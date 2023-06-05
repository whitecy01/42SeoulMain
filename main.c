/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:18:38 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/03 00:43:16 by jaeyojun         ###   ########seoul.kr  */
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

t_node	*create_node(int content)
{
	t_node	*pr;

	pr = (t_node *)malloc(sizeof(t_node));
	pr->content = content;
	pr->prev = NULL;
	pr->next = NULL;
	
	return (pr);
}

void	ft_lstadd_back(t_node **lst, t_node *new)
{
	t_node	*tmp;

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

// void	push_node(int *array, int array_size, t_stack *a)
// {
// 	t_node *pr;
// 	int i = 0;

// 	printf("%d\n", array[1]);
// 	while (i < array_size)
// 	{
// 		pr = create_node(array[i]);
// 		ft_lstadd_back(&a, pr);
// 		pr = pr->top;
// 		i++;
// 	}
// }

t_node *create_node_2(t_node **pr, t_node *new)
{
	t_node  *tmp;

	if (*pr == NULL)
	{
		*pr = new;
		return (NULL);
	}
	if (!new)
		return (NULL);
	tmp = *pr;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
	new->prev = tmp;
}

void	push_node(t_stack **a, int five, int *array)
{
	int i;
	t_node *new_node;
	t_node	*pr;
	
	new_node = create_node(array[0]);
	if (!(((*a)->top)))
		(*a)->top = new_node;
	if (five == 1)
	{
		(*a)->bottom = new_node;
		new_node->next = (*a)->top;
		return ;
	}
	i = 1;
	while (i < five)
	{
		pr = create_node(array[i]);
		create_node_2(&new_node, pr);
		i++;
	}
	(*a)->bottom = pr;
	pr->next = (*a)->top;
}


int	main(void)
{
	//t_node *pr;
	t_stack *a;

	a = create_stack(5, 'a');
	//int array[5] = {1,2,3,4,5};
	int array[5] = {1,2,3,4,5};
	push_node(&a, 5, array);
	//printf("---");
	printf("top %d\n", a->top->content);
	printf("bo %d\n", a->bottom->next->content);

	//push_node(array, 5, a);
	//printf("%d", a->top->content);
	//push_intarray;
}
