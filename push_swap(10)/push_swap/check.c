/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:32:00 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/23 13:20:45 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./checker.h"

// #include <stdio.h>
// int		print_max = 0;
// void    check_list(t_stack **a, t_stack **b)
// {
// 	if (print_max == 3000)
// 		return ;//exit(1);
// 	print_max++;
// 	printf("print_max_idx: %d\n", print_max);
//     printf("\n");
//     int    cnt = 1;
//     printf("============\t============\n");
	
// 	t_node *aa;
// 	t_node *bb;
	
// 	aa = (*a)->top;
// 	bb = (*b)->top;
//     while (aa || bb)
//     {
//         if (aa)
//         {
//             printf("A_ %d: %d", cnt, aa->content);
//             aa = aa->next;
//         }
//         printf("\t\t");
//         if (bb)
//         {
//             printf("B_ %d: %d", cnt, bb->content);
//             bb = bb->next;
//         }
//         printf("\n");
//         cnt++;
// 		if (aa == NULL && bb == NULL)
// 			break ;
//     }
//     printf("============\t============\n\n");
// }

int	count_array(char *temp)
{
	int	i;

	i = 0;
	while (temp[i])
		i++;
	return (i);
}

int	check_newline(char *temp)
{
	int	i;
	int	count;

	i = 0;
	if (!temp)
		return (1);
	count = count_array(temp);
	if (temp[count - 1] != '\n')
		print_error(-1);
	if (temp[i] == '\n')
	{
		return (1);
	}
	return (0);
}

int	sort_check_stack(t_stack **a)
{
	t_node	*tmp;

	tmp = (*a)->top;
	while (tmp->next)
	{	
		if (tmp->content > tmp->next->content)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	checker_yes(t_stack **a, t_stack **b)
{
	char	*temp;

	temp = get_next_line(0);
	while (temp)
	{
		check_command(temp, a, b);
		temp = get_next_line(0);
	}
	if (sort_check_stack(a) == 0)
		write(1, "KO\n", 3);
	else
		write(1, "OK\n", 3);
}

int	main(int argc, char **argv)
{
	char	**array_split;
	int		*array;
	int		array_size;
	t_stack	*a;
	t_stack	*b;

	if (argc < 2)
		return (0);
	array_size = 0;
	array_split = check_input_spilt(argc, argv, &array_size);
	array = change_int(array_split, &array_size);
	array_split = ft_free(array_split);
	a = create_stack(array_size, A);
	b = create_stack(array_size, B);
	stack_a_push_node(array, array_size, &a);
	checker_yes(&a, &b);
}
