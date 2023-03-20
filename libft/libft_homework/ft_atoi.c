/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 17:07:50 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/03/19 17:19:29 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *string)
{
	int	i;
	int	sr;
	int	result;

	result = 0;
	sr = 1;
	i = 0;
	while (string[i] != '\0' && string[i] == '\t')
		i++;
	if (string[i] == '-')
		sr *= -1;
	else if (string[i] == '+')
		;
	while (string[i] != '\0' && (string[i] >= '0' && string[i] <= '9'))
	{
		result = result * 10 + (string[i] - '0');
		i++;
	}
	return (result * sr);
}
