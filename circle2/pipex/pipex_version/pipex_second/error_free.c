/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:27:46 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/04 14:35:52 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *error)
{
	int	i;

	i = 0;
	while (error[i])
	{
		write(1, &error[i], 1);
		i++;
	}
	exit(1);
}

char	**ft_free(char **word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		free(word[i]);
		i++;
	}
	free(word);
	return (0);
}