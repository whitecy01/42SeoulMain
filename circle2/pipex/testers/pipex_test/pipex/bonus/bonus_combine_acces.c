/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_combine_acces.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 15:43:00 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/16 20:22:49 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./bonus_head/pipex.h"

char	*combine_command(char *first_loc_command, char **path)
{
	char	*combine;
	int		i;
	char	*tmp;
	int		fd;

	fd = access(first_loc_command, X_OK);
	if (fd != -1)
		return (first_loc_command);
	combine = ft_strjoin_gnl("/", first_loc_command);
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin_gnl(path[i], combine);
		fd = access(tmp, X_OK);
		if (fd != -1)
		{
			free(combine);
			return (tmp);
		}
		close(fd);
		free(tmp);
		i++;
	}
	free(combine);
	return (NULL);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		count;
	char	*temp;

	if (!s1 || !s2)
		return (NULL);
	count = count_str(s1);
	count += count_str(s2);
	temp = (char *)malloc(sizeof(char) * count + 1);
	if (!temp)
		return (0);
	while (*s1)
	{
		*temp = *s1;
		s1++;
		temp++;
	}
	while (*s2)
	{
		*temp = *s2;
		s2++;
		temp++;
	}
	*temp = '\0';
	return ((temp - count));
}
