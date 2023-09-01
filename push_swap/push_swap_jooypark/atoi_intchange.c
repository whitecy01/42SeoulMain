/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_intchange.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:04:31 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/06/25 21:01:32 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

long	atoi_while(char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i])
	{
		if ('0' <= str[i] && str[i] <= '9')
			result = (10 * result) + str[i] - '0';
		else
			print_error(-1);
		i++;
	}
	if (i >= 11)
		print_error(-1);
	return (result);
}
