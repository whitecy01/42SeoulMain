/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:32:00 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/19 22:38:50 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	print_error(int error)
{
	if (error == -1)
		write(2, "Error\n", 6);
	exit(1);
}

int	check_newline(char *temp)
{
	int i;

	i = 0;
	if (temp[i] == '\n')
		return (1);
	return (0);
}

void	checker_yes(t_stack **a, t_stack **b, int array_size)
{
	char *temp;
	(void) array_size;

	printf("%d %d\n", (*a)->size, (*b)->size);
	temp = get_next_line(0);
	// while (1)
	// {
	// 	if (check_newline(temp) == 1)
	// 		break ;
	// 	temp = get_next_line(0);
	// }
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
	a = create_stack(array_size, A);
	b = create_stack(array_size, B);
	stack_a_push_node(array, array_size, &a);
	checker_yes(&a, &b, array_size);
}
