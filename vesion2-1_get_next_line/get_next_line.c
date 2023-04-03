/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:24:29 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/04/03 21:07:43 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

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

char	*readline(int fd, char *line)
{
	char	buff[BUFFER_SIZE + 1];
	int		readcount;
	char	*tmp;

	readcount = 1;
	if (!line)
		line = ft_strdup("");
	while (readcount)
	{
		readcount = read(fd, buff, BUFFER_SIZE);
		if (readcount == 0)
			break ;
		else if (readcount == -1)
		{
			// free(line);
			// line = NULL;
			return (0);
		}
		buff[readcount] = '\0';
		printf("%s", buff);
		tmp = ft_strjoin(line, buff, readcount);
		if (!line)
			return (NULL);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (tmp);
}

// static char	*ft_checkline(char *line)
// {
// 	int		i;
// 	char	*backup;
// 	int		len_line;

// 	i = 0;
// 	if (!line)
// 		return (0);
// 	while (line[i] != '\0' && line[i] != '\n')
// 		i++;
// 	if (line[i] == '\0')
// 		return (0);
// 	len_line = ft_strlen(line);
// 	backup = ft_substr(line, i + 1, len_line - i);
// 	if (!backup)
// 		return (NULL);
// 	if (backup[0] == '\0')
// 	{
// 		free(backup);
// 		backup = NULL;
// 		return (NULL);
// 	}
// 	return (backup);
// }

// int	len_check(char *line)
// {
// 	int i;

// 	i = 0;
// 	if (!line)
// 		return (0);
// 	while (line[i] != '\0')
// 	{
// 		if (line[i] == '\n')
// 			break ;
// 		i++;
// 	}
// 	return (i);
// }

// char	*change_line(char *line)
// {
// 	int	i;
// 	int count;
// 	char 	*temp;

// 	if (!line)
// 		return (0);
// 	i = 0;
// 	count = len_check(line);
// 	temp = ft_substr(line, i, count + 1);
// 	while (i <= count)
// 	{
// 		temp[i] = line[i];
// 		i++;
// 	}
// 	temp[i] = '\0';
// 	if (!temp)
// 		return (NULL);
// 	if (temp[0] == '\0')
// 	{
// 		free(temp);
// 		temp = NULL;
// 		return (NULL);
// 	}
// 	return (temp);
//}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*line;
	char		*temp = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (backup)
	{
		line = ft_strdup(backup);
		if (!line)
			return (NULL);
		free(backup);
		backup = NULL;
	}
	else
		line = NULL;
	//printf("debuf");
	line = readline(fd, line);
	// if (!line)
	// 	return (NULL);
	//printf("%s", line);
	// backup = ft_checkline(line);
	// temp = change_line(line);
	// free(line);
	// if (!temp)
	// 	return (0);
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

int main(void)
{
  int fd;

  fd = 0;
  fd = open("./test.txt", O_RDONLY);
  char *line;
  int a =1;
  while (a)
  {
	line  = get_next_line(fd);
	// if (line == 0)
	// 	break;
	//printf("%s", line);
	a--;
  }

	free(line);
	// while(1)
	// {

	// }
//   printf("%p\n", line);
//   printf("%s", line);

//   return (0);
}