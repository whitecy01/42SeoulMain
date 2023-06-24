/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 03:37:39 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/23 19:54:06 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"


#include <stdio.h>

void print_error(int error)
{
	if (error == -1)
		write(2, "Error\n", 6);
	exit(1);
}

int print_max = 0;
void check_list(t_stack **a, t_stack **b)
{
	if (print_max == 3000)
		return; // exit(1);
	print_max++;
	printf("print_max_idx: %d\n", print_max);
	printf("\n");
	int cnt = 1;
	printf("============\t============\n");

	t_node *aa;
	t_node *bb;

	aa = (*a)->top;
	bb = (*b)->top;
	while (aa || bb)
	{
		if (aa)
		{
			printf("A_ %d: %d", cnt, aa->content);
			aa = aa->next;
		}
		printf("\t\t");
		if (bb)
		{
			printf("B_ %d: %d", cnt, bb->content);
			bb = bb->next;
		}
		printf("\n");
		cnt++;
		if (aa == NULL && bb == NULL)
			break;
	}
	printf("============\t============\n\n");
}

int main(int argc, char **argv)
{
	int array_size;
	char **array_split;
	int *array;
	t_stack *a;
	t_stack *b;

	if (argc < 2)
		print_error(-1);
	array_size = 0;
	array_split = check_input_spilt(argc, argv, &array_size);
	if (array_size == 0)
		print_error(-1);
	array = change_int(array_split, &array_size);
	array_split = ft_free(array_split);
	a = create_stack(array_size, A);
	b = create_stack(array_size, B);
	stack_a_push_node(array, array_size, &a);
	free(array);
	if (check_sorted(a->top, array_size, A))
		return (0);
	a->flag = 1;
	sort_algorithm(&a, &b, array_size);
	check_list(&a,&b);
	return (0);
}
