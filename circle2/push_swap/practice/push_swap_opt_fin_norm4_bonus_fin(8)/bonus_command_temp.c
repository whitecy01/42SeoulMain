/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_command_temp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:55:16 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/22 16:18:48 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./checker.h"

void	check_two_command(char *temp)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		if (i == 0)
		{
			if (!(temp[i] == 'p' || temp[i] == 's' || temp[i] == 'r'))
				print_error(-1);
		}
		else if (i == 1)
		{
			if (!(temp[i] == 'a' || temp[i] == 'b' || temp[i] == 'r'))
				print_error(-1);
		}
		else if (i == 2)
		{
			if (temp[i] != '\n')
				print_error(-1);
		}
		i++;
	}
}

void	check_three_command(char *temp)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		if (i == 0 || i == 1)
		{
			if (!(temp[i] == 'r'))
				print_error(-1);
		}
		else if (i == 2)
		{
			if (!(temp[i] == 'a' || temp[i] == 'b' || temp[i] == 'r'))
				print_error(-1);
		}
		else if (i == 3)
		{
			if (temp[i] != '\n')
				print_error(-1);
		}
		i++;
	}
}

void	check_temp(char *temp)
{
	int	count;

	if (!temp)
		return ;
	count = count_array(temp);
	if (!((count == 3) || count == 4))
		print_error(-1);
	if (count == 3)
		check_two_command(temp);
	else if (count == 4)
		check_three_command(temp);
}
