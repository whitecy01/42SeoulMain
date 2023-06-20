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

#include "./head/checker.h"

void print_error(int error)
{
	if (error == -1)
		write(2, "Error\n", 6);
	exit(1);
}

int count_array(char *temp)
{
	int i = 0;
	while (temp[i])
		i++;
	return (i);
}

int check_newline(char *temp)
{
	int i;

	i = 0;
	int count = count_array(temp);
	if ( temp[count - 1] != '\n')
	{
		write(1, "Error\n", 6);
		exit(1);
	}
	if (temp[i] == '\n')
	{
		return (1);
	}
	return (0);
}

void	sort_alo_checker(t_stack **a, t_stack **b, char *temp)
{
	int i;

	i = 0;
	//체커 확인해봐야함
	//1. pa 같은 거를 그냥 띄어쓰기 해서 넣어도 되는지 아니면 그거 없이 해야하는지 
}

void checker_yes(t_stack **a, t_stack **b, int array_size)
{
	char *temp;

	printf("%d %d %d\n", (*a)->size, (*b)->size, array_size);
	temp = get_next_line(0);
	printf("temp : %s\n", temp);
	while (temp)
	{
		if (check_newline(temp) == 1)
			break;
		sort_alo_checker(a, b, temp);

		temp = get_next_line(0);
	}
}

int main(int argc, char **argv)
{
	char **array_split;
	int *array;
	int array_size;
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
	checker_yes(&a, &b, array_size);
}
