/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 03:37:39 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/18 04:03:42 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../head/push_swap.h"

void	print_error(int error)
{
	if (error == -1)
		write(2, "Error\n", 6);
	exit(1);
}

// int	check_sort(t_stack **a, int array_size)
// {
// 	t_node	*tmp;
// 	int		check;

// 	tmp = (*a)->top;
// 	check = tmp->content;
// 	while (array_size--)
// 	{
// 		check = tmp->content;
// 		if ((tmp->next) && check > tmp->next->content)
// 			return (0);
// 		tmp = tmp->next;
// 	}
// 	return (1);
// }

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
	a = create_stack(array_size, A);
	b = create_stack(array_size, B);
	stack_a_push_node(array, array_size, &a);
	a->flag = 1;
	sort_algorithm(&a, &b, array_size);
}
