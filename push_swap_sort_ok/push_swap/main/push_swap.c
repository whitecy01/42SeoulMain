/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:19:08 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/16 17:36:54 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../head/push_swap.h"

int		print_max = 0;
void    check_list(t_stack **a, t_stack **b)
{
	if (print_max == 3000)
		return ;//exit(1);
	print_max++;
	printf("print_max_idx: %d\n", print_max);
    printf("\n");
    int    cnt = 1;
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
			break ;
    }
    printf("============\t============\n\n");
}


void	print_error(int error)
{
	if (error == -1)
		write(2, "Error\n", 6);
	exit(1);
}

int		check_sort(t_stack **a, int array_size)
{
	t_node *tmp;
	tmp = (*a)->top;

	int check = tmp->content;
	printf("array_size : %d\n", array_size);
	while (array_size--)
	{
		check = tmp->content;
		
		if ((tmp->next) && check > tmp->next->content)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int		array_size;
	char	**array_split;
	int		*array;
	t_stack	*a;
	t_stack	*b;

	if (argc < 2)
		print_error(-1);
	array_size = 0;
	array_split = check_input_spilt(argc, argv, &array_size);
	if (array_size == 0)
		print_error(-1);
	array = change_int(array_split, &array_size);
	array_split = ft_free(array_split);
	a = create_stack(array_size, 'a');
	b = create_stack(array_size, 'b');
	stack_a_push_node(array, array_size, &a);
	// while (a->top)
	// {
	// 	printf("a->top : %d\n" , a->top->content);
	// 	a->top = a->top->next;
	// }
	// while (a->bottom)
	// {
	// 	printf("a->bottom : %d\n" , a->bottom->content);
	// 	a->bottom = a->bottom->prev;
	// }
	//check_list(&a, &b);
	sort_algorithm(&a, &b, array_size);
	//check_list(&a, &b);
	//printf("DONE\n");
	// if (check_sort(&a, array_size) == 1)
	// 	printf("SUC\n");
	// else
	// 	printf("FAIL\n");
}
