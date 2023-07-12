/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:27:46 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/07 17:59:14 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./head/pipex.h"

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


char	*ft_free_one(char *word)
{
// 	int	i;

// 	i = 0;
// 	while (word[i])
// 	{
// 		free(word[i]);
// 		i++;
// 	}
	free(word);
	return (0);
}