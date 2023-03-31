/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 01:57:57 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/03/31 18:23:18 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// #include <stdio.h>
// #include <fcntl.h>


//static char	*ft_nonewline(char *line);
// char	*ft_check_null(char *line)
// {
// 	int		i;
// 	char	*temp;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	while (line[j] != '\0' && line[j] != '\n')
// 		j++;
// 	if (line[++j] == '\0')
// 		return (0);
// 	temp = (char *)malloc(sizeof(char) * j + 1);
// 	if (!temp)
// 		return (0);
// 	while (line[i] != '\0' && j--)
// 	{
// 		temp[i] = line[i];
// 		i++;
// 	}
// 	temp[i] = '\0';
// 	return (temp);
// }

char	*ft_readline(int fd, char *buff, char *backup)
{
	int		reada;
	char	*line;

	reada = 1;
	while (reada)
	{
		reada = read(fd, buff, BUFFER_SIZE);
		if (reada == 0)
			break ;
		if (reada == -1)
		{
			free(backup);
			return (0);
		}
		buff[reada] = '\0';
		if (!backup)
			backup = ft_strdup("");
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

char	*ft_nonewline(char *line)
{
	char	*newline;
	int		count;
	int		count2;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!line)
		return (0);
	newline = NULL;
	if (!newline)
		newline = ft_strdup("");
	count = ft_strlen(line);
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	count2 = count - i;
	i++;
	while (line[i] != '\0' && j < count2)
	{
		newline[j] = line[i];
		j++;
	}
	newline[j] = '\0';
	line[i + 1] = '\0';
	return (newline);
}

char	*get_next_line(int fd)
{
	char		buff[BUFFER_SIZE + 1];
	static char	*backup;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	line = ft_readline(fd, buff, backup);
	backup = ft_nonewline(line);
//	line = ft_check_null(line);
	if (!line)
		return (0);
	return (line);
}


// int main(void)
// {
//   int fd;

//   fd = open("./test.txt", O_RDONLY);
//   char *line;
// 	int a = 1;
//   while (a--)
//   {
// 	line  = get_next_line(fd);
// 	printf("%s", line);
//   }

// //   printf("%p\n", line);
// //   printf("%s", line);

//   return (0);
// }