/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_empty_overlap.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:00:13 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/22 16:18:55 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./checker.h"

void	empty_string_number_check(char *argv)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = 0;
	while (argv[i] != '\0')
	{
		if (argv[i] >= '0' && argv[i] <= '9')
			tmp = 1;
		i++;
	}
	if (tmp == 0)
		print_error(-1);
}

void	overlap_check(int *temp, int array_size)
{
	int	i;
	int	j;

	i = 0;
	while (i < array_size)
	{
		j = i + 1;
		while (j < array_size)
		{
			if (temp[i] == temp[j])
				print_error(-1);
			j++;
		}
		i++;
	}
}
