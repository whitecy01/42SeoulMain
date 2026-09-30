/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_error_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:00:18 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/25 17:35:32 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	error(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(2, &s[i], 1);
		i++;
	}
	exit(1);
	return (0);
}

void	ft_free(char *tmp)
{
	free(tmp);
	tmp = NULL;
}

char	*boom_map_buff(char *line, char *map_buf)
{
	ft_free(line);
	ft_free(map_buf);
	return (NULL);
}
