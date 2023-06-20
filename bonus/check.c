/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:32:00 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/20 17:39:11 by jaeyojun         ###   ########seoul.kr  */
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

	if (!temp)
		return (1);

	int count = count_array(temp);
	if (temp[count - 1] != '\n')
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

void	check_temp(char *temp)
{
	int i;
	int count;
	
	write(1, "awd\n", 4);
	if (!temp)
		return ;
	write(1, "awd\n", 4);
	count = count_array(temp);
	if (count != 3)
	{
		write(1, "Error\n", 6);
		exit(1);
	}
	i = 0;
	while(temp[i])
	{
		if (i == 0 || i == 1)
			if (!(temp[i] >= 'a' && temp[i] <= 'z'))
			{
				write(1, "Error\n", 6);
				exit(1);
			}
		if (i == 2)
			if(temp[i] != '\n')
			{
				write(1, "Error\n", 6);
				exit(1);
			}
	}
	i++;
}
//pa pb sa sb ss 
void	command_p(char *temp, t_stack **a, t_stack **b)
{
	int i;

	i = 0;
	if (temp[i] == 'a')
		pa(a, b);
	else if (temp[i] == 'b')
		pb(a, b);
}

void	command_s(char *temp, t_stack **a, t_stack **b)
{
	int i;

	i = 0;
	if (temp[i] == 'a')
		sa(a);
	else if (temp[i] == 'b')
		sb(b);
	else if (temp[i] == 's')
		ss(a, b);
}

//ra rb rr rra rrb rrr
void	command_r(char *temp, t_stack **a, t_stack **b)
{
	int i;

	i = 1;
	if (temp[i] == 'a')
		sa(a);
	else if (temp[i] == 'b')
		sb(b);
	else if (temp[i] == 'r')
		ss(a, b);
}

void	command_rr(char *temp, t_stack **a, t_stack **b)
{
	int i;

	i = 2;
	if (temp[i] == 'a')
		ra(a);
	else if (temp[i] == 'b')
		rb(a);
	else if (temp[i] == 'r')
		rr(a, b);
}

void	check_command(char *temp, t_stack **a, t_stack **b)
{
	int i;

	i = 0;
	if (temp[i] == 'p')
		command_p((temp + i), a, b);
	else if (temp[i] == 's')
		command_s((temp + i), a, b);
	else if (temp[i] == 'r')
	{
		if (temp[i + 1] == 'r')
			command_rr((temp + i), a, b);
		else
			command_r((temp + i), a, b);
	}
}

int	sort_check_stack(t_stack **a)
{
	t_node *tmp;

	tmp = (*a)->top;
	
	while (tmp->next)
	{	
		if (tmp->content > tmp->next->content)
			return (0);
		tmp = tmp->next;
	}
	printf("debug\n");
	return (1);
}

void	sort_alo_checker(t_stack **a, t_stack **b, char *temp)
{
	int i;

	i = 0;
	//체커 확인해봐야함
	//1. 명령어는 무조건 다른 거 없이 넣어야함
	//체크하는 함수 넣자
	
	check_temp(temp);
	if(!temp)
		return ;
	write(1, "check\n", 4);
	check_command(temp, a, b);
}

void	input_one(t_stack **a, char *temp)
{
	if (check_newline(temp) == 1)
		;
	if (sort_check_stack(a) == 0)
		write(1, "KO\n", 3);
	else
		write(1, "OK\n", 3);
}

void checker_yes(t_stack **a, t_stack **b)
{
	char *temp;

	temp = get_next_line(0);
	printf("temp : %s\n", temp);

	// if (!temp)
	// {
	// 	input_one(a, temp);
	// 	return ;
	// }
	while (temp)
	{
		
		if (check_newline(temp) == 1)
			break ;

		temp = get_next_line(0);
	}
	write(1, "awd\n", 4);
	sort_alo_checker(a, b, temp);
	if (sort_check_stack(a) == 0)
	{
		write(1, "KO\n", 3);
	}
	else
	{
		write(1, "OK\n", 3);
	}
}

int main(int argc, char **argv)
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
