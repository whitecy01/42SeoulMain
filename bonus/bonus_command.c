/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:40:10 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/22 15:54:18 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./head/checker.h"

void	command_p(char *temp, t_stack **a, t_stack **b)
{
	int	i;

	i = 1;
	if (temp[i] == 'a')
		pa(a, b);
	else if (temp[i] == 'b')
		pb(a, b);
}

void	command_s(char *temp, t_stack **a, t_stack **b)
{
	int	i;

	i = 1;
	if (temp[i] == 'a')
		sa(a);
	else if (temp[i] == 'b')
		sb(b);
	else if (temp[i] == 's')
		ss(a, b);
}

void	command_r(char *temp, t_stack **a, t_stack **b)
{
	int	i;

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
	int	i;

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
	int	i;

	i = 0;
	check_temp(temp);
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
