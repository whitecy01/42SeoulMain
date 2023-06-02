/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_stacknode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:25:19 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/05/29 21:10:50 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

void    create_node(int *array, int array_size, t_stack **a)
{
    //t_node *array_input_node;
    //t_stack *a_loc;

    printf("a->size : %d\n")
    // a_loc = *a;
    // while()
    // {
    //     tmp = (t_stack *)malloc(sizeof(t_stack))
    //     {

    //     }
    // }


}