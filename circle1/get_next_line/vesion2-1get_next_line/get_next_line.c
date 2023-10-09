/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:24:29 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/04/05 20:38:55 by jaeyojun         ###   ########seoul.kr  */
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
		if (readcount == 0)
			break ;
		else if (readcount == -1)
		{
			free(line);
			line = NULL;
			return (0);
		}
		buff[readcount] = '\0';
		line = ft_strjoin(line, buff, readcount);
		if (!line)
			return (NULL);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (line);
}

static char	*ft_checkline(char *line, char **backup)
{
	int		i;
	//char	*backup;
	int		len_line;

	i = 0;
	// if (!(*backup))
	// {
	// 	*backup = NULL;
	// 	return(NULL);
	// }
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
	{
		// free(line);
		// line = NULL;
		//*backup = NULL;
		return (NULL);
	}
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
	{
		return (0);
	}
	while (line[i] != '\0')
	{
		if (line[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*change_line(char **line)
{
	int		i;
	int		count;
	char	*temp;

	i = 0;
	if (!(*line))
	{
		//free(*line);
		//*line = NULL;
		return (NULL);
	}
	count = len_check(*line);
	if (count == -1)
	{
		temp = ft_strdup(*line);
		if (!temp)
		{
			temp = NULL;
			return (NULL);
		}
	}
	else
	{
		temp = ft_substrab(*line, i, count + 1);
		if (!temp)
		{
			temp = NULL;
			return (NULL);
		}
	}
	return (temp);
}

// char	*get_next_line(int fd)
// {
// 	static char	*backup;
// 	char		*line;
// 	char		*temp;

// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	line = readline(fd, backup);
// 	if (!line)
// 	{
// 		free(backup);
// 		backup = NULL;
// 		return (NULL);
// 	}
// 	backup = ft_checkline(line);
// 	if (!backup)
// 	{
// 		free(line);
// 		line = NULL;
// 		free(backup);
// 		backup = NULL;
// 		return (NULL);
// 	}
// 	temp = change_line(line);
// 	free(line);
// 	line = NULL;
// 	if (!temp)
// 	{
// 		free(backup);
// 		backup = NULL;
// 		return (NULL);
// 	}
// 	return (temp);
// }

// char	*check_newline(char **line)
// {
// 	int		i;
// 	char 	*backup;
// 	int		len_line;
// 	char	*temp;


// 	if (!line)
// 	{
// 		line = NULL;
// 		return (NULL);
// 	}
// 	i = 0;
// 	len_line = ft_strlen(*line);
// 	while (*line[i] != '\0' && *line[i] != '\n')
// 	{
// 		i++;
// 	}
// 	if (*line[i] == '\0')
// 		return (NULL);
// 	backup = ft_substr(*line, i + 1, len_line - i);
// 	if (!backup)
// 	{
// 		free(backup);
// 		backup = NULL;	
// 		return (NULL);
// 	}
// 	temp = ft_substr(*line, 0, i + 1);
// 	free(*line);
// 	*line = temp;
// 	free(temp);
// 	return (backup);
// }


char	*get_next_line(int fd)
{
	static char	*backup;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	//1. backup개행있을 때
	//backup에 있는 친구 개행까지 출력한 다음 다시 backup에 넣기
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
	if (!line)
		return (NULL);
	backup = ft_checkline(line, &backup);
	temp = change_line(&line);
	free(line);
	line = NULL;
	if (!temp)
	{
		free(backup);
		backup = NULL;
		return (NULL);
	}
	return (temp);
}

// char	*get_next_line(int fd)
// {
// 	static char	*backup;
// 	char		*line;
// 	char		*temp;
// 	int			line_len;
	
// 	// 에러체크
// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	// 백업을 먼저 검사
// 	// 있으면, 백업에 있는 문자열을 line에 복사
// 	// 없으면, 백업 줄게 없으니깐 널로 초기화
// 	if (backup)
// 	{
// 		line = ft_strdup(backup);
// 		if (!line)
// 			return (NULL);
// 		free(backup);
// 		backup = NULL;
// 	}
// 	else
// 		line = NULL;
// 	// line은 백업을 받아왔으니깐 make_buff 함수는 버퍼사이즈만큼 line 붙여주는 것
// 	// 백업 0123456\n7
// 	line = make_buff(line, fd, 0);
// 	if (!line)
// 		return (NULL);
// 	line_len = ft_linelen(line);
// 	// line : 012345\n
// 	// temp : 012345\n
// 	// backup : 
// 	temp = make_line(line, line_len);
// 	backup = make_cache(line, temp, line_len);
// 	free(line);
// 	return (temp);
// }

// int main(void)
// {
//   int fd;

//   fd = 0;
//   fd = open("./test1.txt", O_RDONLY);
//   char *line;
//   int a =1;
//   while (a)
//   {
// 	line  = get_next_line(fd);
// 	// if (line == 0)
// 	// 	break;
// 	printf("%s", line);
// 	a--;
//   }

// 	free(line);
// 	// while(1)
// 	// {

// 	// }
// //   printf("%p\n", line);
// //   printf("%s", line);

// //   return (0);
// }