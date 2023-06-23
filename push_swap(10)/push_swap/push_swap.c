/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 03:37:39 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/23 13:34:51 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_error(int error)
{
	if (error == -1)
		write(2, "Error\n", 6);
	exit(1);
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
	//argv = ft_free(argv);
	a = create_stack(array_size, A);
	b = create_stack(array_size, B);
	stack_a_push_node(array, array_size, &a);
	if (check_sorted(a->top, array_size, A))
		return (0);
	a->flag = 1;
	sort_algorithm(&a, &b, array_size);
}
