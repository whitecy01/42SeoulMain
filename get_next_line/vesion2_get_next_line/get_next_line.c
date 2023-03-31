/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:24:29 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/03/31 17:52:50 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strcat(char *str2, char *str1)
{
	int		i;
	int		count;
	char	*temp;
	int		j;

	i = 0;
	j = 0;
	count = ft_strlen(str2) + ft_strlen(str1);
	temp = (char *)malloc(sizeof(char) * count + 1);
	while (str1[i] != '\0')
	{
		temp[i] = str1[i];
		i++;
	}
	while (str2[j] != '\0')
	{
		temp[i] = str2[j];
		i++;
		j++;
	}
	temp[i] = '\0';
	return (temp);
}

char	*check_leaks_buff(char *check_leaks, int readcount)
{
	int	i;

	i = ft_strlen(check_leaks);
	if (i == readcount)
		return (check_leaks);
	else
	{
		check_leaks[i] = '\0';
		return (check_leaks);
	}
}

char	*readline(int fd, char *backup)
{
	char	buff[BUFFER_SIZE + 1];
	int		readcount;
	char	*line;

	readcount = 1;
	while (readcount)
	{
		readcount = read(fd, buff, BUFFER_SIZE);
		if (readcount == 0)
		{
			break ;
		}
		else if (readcount == -1)
		{
			free(backup);
			return (0);
		}
		buff[readcount] = '\0';
		if (!backup)
			backup = ft_strdup("");
		line = backup;
		backup = ft_strjoin(line, buff);
		if (!backup)
		{
			return (0);
		}
		free (line);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (backup);
}

static char	*ft_checkline(char *line)
{
	int		i;
	char	*backup;

	i = 0;
	if (!line)
		return (0);
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return (0);
	backup = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (!backup)
		return (NULL);
	if (backup[0] == '\0')
	{
		free(backup);
		backup = NULL;
		return (NULL);
	}
	line[i + 1] = '\0';
	return (backup);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*backup;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		return (NULL);
	}
	line = readline(fd, backup);
	backup = ft_checkline(line);
	if (!line)
	{
		return (NULL);
	}
	return (line);
}

// int main(void)
// {
//   int fd;

//   fd = 0;
//   fd = open("./test.txt", O_RDONLY);
//   char *line;
//   while (1)
//   {
// 	line  = get_next_line(fd);
// 	if (line == 0)
// 		break;
// 	printf("%s", line);
//   }

// 	free(line);
// 	while(1)
// 	{

// 	}
// //   printf("%p\n", line);
// //   printf("%s", line);

//   return (0);
// }