/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 01:57:57 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/03/31 13:56:06 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char	*ft_nonewline(char *line)
{
	char	*newline;
	int		count;
	int		count2;
	int		i;
	int		j;

	j = 0;
	i = 0;
	newline = NULL;
	if (!newline)
		newline = ft_strdup("");
	count = ft_strlen(line);
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	count2 = count - i;
	i++;
	while (line[i] != '\0' && count2)
	{
		newline[j++] = line[i++];
		count2--;
	}
	newline[j] = '\0';
	return (newline);
}

char	*ft_readline(int fd, char *buff, char *backup)
{
	int		reada;
	char	*line;

	reada = 1;
	while (reada)
	{
		reada = read(fd, buff, BUFFER_SIZE);
		if (reada <= -1)
			return (0);
		if (reada == 0)
			break ;
		buff[reada] = '\0';
		line = backup;
		backup = ft_strjoin(line, buff);
		if (!backup)
			return (0);
		free (line);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (backup);
}

char	*ft_check_null(char *line)
{
	int		i;
	char	*temp;
	int		j;

	i = 0;
	j = 0;
	while (line[j] != '\0' && line[j] != '\n')
		j++;
	if (line[++j] == '\0')
		return (0);
	temp = (char *)malloc(sizeof(char) * j + 1);
	if (!temp)
		return (0);
	if (temp[0] == '\0')
	{
		free(temp);
		return (NULL);
	}
	while (line[i] != '\0' && j--)
	{
		temp[i] = line[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*backup;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (0);
	if (!backup)
	{
		backup = ft_strdup("");
	}
	line = ft_readline(fd, buff, backup);
	free (buff);
	backup = ft_nonewline(line);
	line = ft_check_null(line);
	if (!line)
		return (0);
	return (line);
}
