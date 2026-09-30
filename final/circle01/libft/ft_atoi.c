/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 17:07:50 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/03/24 13:06:14 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *string)
{
	int		i;
	long	sr;
	long	result;

	result = 0;
	sr = 1;
	i = 0;
	while (string[i] != '\0' && ((string[i] >= 9 && string[i] <= 13)
			|| string[i] == 32))
		i++;
	if (string[i] == '-')
	{
		sr *= -1;
		i++;
	}
	else if (string[i] == '+')
		i++;
	while (string[i] != '\0' && (string[i] >= '0' && string[i] <= '9'))
	{
		result = result * 10 + (string[i] - '0');
		i++;
	}
	return ((int)(result * sr));
}
