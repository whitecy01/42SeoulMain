/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:24:29 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/04/06 21:44:30 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

char	*readline(int fd, char *line)
{
	char	buff[BUFFER_SIZE + 1];
	int		readcount;

	readcount = 1;
	while (readcount)
	{
		readcount = read(fd, buff, BUFFER_SIZE);
		//printf(" readcount : %d", readcount);
		if (readcount == 0)
			break ;
		else if (readcount == -1)
		{
			free(line);
			line = NULL;
			return (NULL);
		}
		buff[readcount] = '\0';
		line = ft_strjoin(line, buff, readcount, ft_strlen(line));
		if (!line)
			return (NULL);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	//printf("")
	return (line);
}

static char	*ft_checkline(char *line, char **backup)
{
	int		i;
	int		len_line;

	i = 0;
	if (!line)
	{
		line = NULL;
		return (NULL);
	}
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return (NULL);
	len_line = ft_strlen(line);
	*backup = ft_substr(line, i + 1, len_line - i);
	if (!(*backup))
		return (NULL);
	if (*backup[0] == '\0')
	{
		free(*backup);
		line = NULL;
		*backup = NULL;
		return (NULL);
	}
	return (*backup);
}

int	len_check(char *line)
{
	int	i;

	i = 0;
	if (line == 0)
		return (0);
	while (line[i] != '\0')
	{
		if (line[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*change_line(char **line, char **backup)
{
	int		count;
	char	*temp;

	if (!(*line))
		return (NULL);
	count = len_check(*line);
	if (count == -1)
		temp = ft_strdup(*line);
	else
		temp = ft_substr(*line, 0, count + 1);
	if (!temp)
	{
		free(*backup);
		*backup = NULL;
		temp = NULL;
		return (NULL);
	}
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (backup)
	{
		line = ft_strdup(backup);
		free(backup);
		backup = NULL;
		if (!line)
			return (NULL);
	}
	else
		line = NULL;
	line = readline(fd, line);
	printf("debuf");
	if (!line)
		return (NULL);
	//printf("debuf");
	backup = ft_checkline(line, &backup);
	temp = change_line(&line, &backup);
	free(line);
	if (!temp)
		return (NULL);
	return (temp);
}

#include <fcntl.h>

int main(void)
{
  int fd;

  fd = 0;
  fd = open("./test.txt", O_RDONLY);
  char *line;
  //int a =3;
  while (1)
  {
	//printf("%s\n", get_next_line(fd));
	//printf("%p\n", get_next_line(fd));
	line= get_next_line(fd);
	// if (line == 0)
	// 	break;
	printf("%s\n", NULL);
	printf("%c\n", '\0');
	printf("%s\n", line);
	//printf("%p\n", line);
	if (line == 0)
		break;
	//a--;
  }

	free(line);
	// while(1)
	// {

	// }
//   printf("%p\n", line);
//   printf("%s", line);

//   return (0);
}
