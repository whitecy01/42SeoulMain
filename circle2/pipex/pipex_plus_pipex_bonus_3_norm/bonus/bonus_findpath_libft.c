/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_findpath_libft.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:24:56 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/16 15:44:28 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./bonus_head/pipex.h"

int	number_compare(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	while ((str1[i] != '\0' || str2[i] != '\0') && i < n)
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}

char	**find_path(char **envp)
{
	int		i;
	char	**envp_split_reslt;

	i = 0;
	while (number_compare(envp[i], "PATH", 4) != 0)
		i++;
	envp_split_reslt = envp_split(envp[i]);
	i = 0;
	while (envp_split_reslt[i])
		i++;
	return (envp_split_reslt);
}

int	count_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
