/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_path_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:25:48 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/16 20:23:49 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./bonus_head/pipex.h"

int	separator_slash(char tmp)
{
	if (tmp == '/')
		return (0);
	return (1);
}

int	separator_colon(char tmp)
{
	if (tmp == ':')
		return (0);
	return (1);
}

char	*word_split(char *envp_path)
{
	int		i;
	int		count;
	char	*tmp;

	i = 0;
	count = count_str(envp_path);
	tmp = (char *)malloc(sizeof(char) * (count + 1));
	if (!tmp)
		return (0);
	while (envp_path[i] && separator_colon(envp_path[i]))
	{
		tmp[i] = envp_path[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

int	ma_count(char *envp_path)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (envp_path[i])
	{
		while (envp_path[i] && separator_slash(envp_path[i]) == 1)
			i++;
		if (envp_path[i])
			count++;
		while (envp_path[i] && separator_colon(envp_path[i]) == 1)
			i++;
	}
	return (count);
}

char	**envp_split(char *envp_path)
{
	char	**envp_split_result;
	int		malloc_count;
	int		size;

	malloc_count = 0;
	size = ma_count(envp_path);
	envp_split_result = (char **)malloc(sizeof(char *) * (size + 1));
	if (!envp_split_result)
		return (0);
	while (*envp_path)
	{
		while (*envp_path && separator_slash(*envp_path) == 1)
			envp_path++;
		if (*envp_path)
		{
			envp_split_result[malloc_count++] = word_split(envp_path);
			if (envp_split_result[malloc_count - 1] == 0)
				return (ft_free(envp_split_result));
			envp_path++;
		}
		while (*envp_path && separator_colon(*envp_path) == 1)
			envp_path++;
	}
	envp_split_result[malloc_count] = 0;
	return (envp_split_result);
}
